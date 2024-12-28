#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <libgen.h>
#include <unistd.h>

#include "hexdump.h"
#include "iostream.h"


#define BUFIZE 16



#define log_error(fmt, ...)     printf("\033[31m" fmt "\033[0m\n", ##  __VA_ARGS__ )
#define log_warning(fmt, ...)   printf("\033[33m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_notice(fmt, ...)    printf("\033[32m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_info(fmt, ...)      printf("\033[37m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_debug(fmt, ...)     printf("\033[34m" fmt "\033[0m\n", ## __VA_ARGS__ )

// 4 + 4 + 2

// ============================================================================
static int
fio_input_multipart_form_data(
    struct context *ctx,
    char *data, size_t dlen
)
// ============================================================================
{
    size_t dofst = 0, rofst = 0;
    char *p0, *p1;
    size_t ofst, size, len, cofst, plen;
    char *boundary;
    char buffer[BUFIZE + 1];
    static bool start;
    static int idx = 0;
    static bool cache = false;
    static size_t clen = 0;
    static char cbuffer[BUFIZE + 1];
    boundary = ctx->content_boundary;


    log_warning("read %d(0x%x) data ...", dlen, dlen);
    hexdump(data, dlen);

    /* check cache */

    // 1. 如果存在cache, 则记录clen的位置;
    // 2. 将cache填充满
    // 3. 记录偏移rofst
    // 4. 更新指针
    p0 = data;
    plen = dlen;
    if (cache) {
        cofst = clen;
        len = (dlen < (BUFIZE - clen)) ? dlen : (BUFIZE - clen);
        memcpy(cbuffer + cofst, data, len);
        clen += len;
        rofst = len;

        log_debug("cache0 data (cache:%d/%d, data:%d/%d)", cofst, clen, dofst, rofst);
        hexdump(cbuffer, clen);

        p0 = cbuffer;
        plen = clen;
    }

    /* check boundary */
    check_boundary:
    // if (cache) {
    //     log_debug("check in cache (cache:%d/%d, data:%d/%d, handle:%d)",
    //         cofst, clen, dofst, rofst, plen);
    // } else {
    //     log_debug("check in data (data:%d/%d, handle:%d)",dofst, rofst, plen);
    // }
    // hexdump(p0, plen);

    while ( (p1 = (char *)memmem(p0, plen, boundary, strlen(boundary))) ) {
        bool suffix = false;

        size  = p1 - p0;
        plen -= size;
        if ((4 <= size) && (0 == strncmp(p1 - 4, "\r\n--", 4))) {
            memset(p1 - 4, 0, 2);
            size -= 4;
        } else if ( (2 <= size) && 0 == strncmp(p1 - 2, "--", 2) ) {
            /* first data */
            size -= 2;
            idx = 1;
            log_notice("==== START ====");
        }

        /* write form data end */
        if ( 0 < size ) {
            log_notice("index: %d, start: %5s, cache: %5s => %d:%s", idx++,
                start ? "true" : "false", cache ? "true" : "false",
                strlen(p0), p0);
            hexdump(p0, size);
        }

        /* next form */
        start = true;
        p0 = p1 + strlen(boundary);
        plen -= strlen(boundary);


        /* update pointer */
        if (cache && (p0 < (cbuffer + cofst))) {
            ofst = (cbuffer + cofst) - p0;
            len = (cbuffer + clen) - p0;
            memcpy(buffer, p0, len);
            memcpy(cbuffer, buffer, len);
            cache = true;
            cofst = ofst;
            clen = len;
            /* copy data */
            ofst = clen;
            size = BUFIZE - clen;
            len = ((dlen - rofst) < size) ? (dlen - rofst) : size;
            memcpy(cbuffer + ofst, (data + rofst), len);
            rofst += len;
            clen += len;

                log_debug("update1 cache (%d/%d, %d/%d)", cofst, clen, dofst, rofst);
                hexdump(cbuffer, clen);

            /* update pointer */
            p0 = cbuffer;
            plen = clen;
        /* */
        } else if (cache) {
            // ofst = p0 - (cbuffer + cofst);
            // log_debug("change1Q cache to data 0x%x/0x%x %d, len:%d", dofst, rofst, ofst, plen);
            // hexdump(p0, plen);

            dofst += p0 - (cbuffer + cofst);
            p0 = data + dofst;
            plen = dlen - dofst;

            // if (2 <= plen && 0 == strncmp(p0, "\r\n", 2)) {
            //     /* skip boundary suffix: \r\n */
            //     p0 += 2;
            //     plen -= 2;
            //     dofst += 2;
            //     suffix = true;
            // }

            cache = false;
            rofst = dofst;

            log_debug("change1 cache to data 0x%x/0x%x len:%d", dofst, rofst, plen);
            hexdump(p0, plen);
        }


        /* */
        if (plen == 4 && 0 == strncmp(p0, "--\r\n", 4)) {
            log_notice("==== END1 ====");
            return 0;
        } else if (2 <= plen && 0 == strncmp(p0, "\r\n", 2)) {
            /* skip boundary suffix: \r\n */
            p0 += 2;
            plen -= 2;
            suffix = true;
        }

        /* */
        if (!cache && !suffix) {
            len = plen + strlen(boundary);
            memcpy(cbuffer, (p0 - strlen(boundary)), len);
            cache = true;
            clen = len;


        }
        if (!cache) {
            dofst = p0 - data;
            rofst = dofst;
        }
    }


    /* check end */
    p0 = cache ? cbuffer : (data + dofst);
    plen = cache ? clen : (dlen - dofst);
    if ( plen == 4 && 0 == strncmp(p0, "--\r\n", 4) ) {
        log_notice("==== END ====");
        return 0;
    }


    /* update cache */
    if ( cache && BUFIZE <= clen ) {
        len = clen;
        size = strlen(boundary) + 4 + 3;
        len -= (size <= BUFIZE) ? size : 0;
        /* */
        memset(buffer, 0, sizeof(buffer));
        memcpy(buffer, cbuffer, len);

        log_notice("#index: %d, start: %5s, cache: %5s => %d:%s", idx,
            start ? "true" : "false", cache ? "true" : "false",
            strlen(buffer), buffer);
        hexdump( buffer, len );

        /* */
        start = false;
        cache = false;
        if (cofst < len) {
            dofst = len - cofst;
            rofst = dofst;
            p0 = data + dofst;
            plen = dlen - dofst;

            log_debug("change2 cahce to data (data:%d/%d)", dofst, rofst);
            hexdump(p0, plen);

        } else {
            size = strlen(boundary) + 4 + 3;
            if ( size <= BUFIZE ) {
                ofst = clen - size;
                memcpy(buffer, cbuffer + ofst, size);
                memcpy(cbuffer, buffer, size);
                cache = true;
                cofst -= len;
                clen = size;

                log_debug("update2 cache (cahce:%d/%d, data:%d/%d)", cofst, clen, dofst, rofst);
                hexdump(cbuffer, clen);

                p0 = cbuffer;
                plen = clen;
            }
        }
        cofst = clen;
    }

    /* cache data */
    ofst = cache ? cofst : 0;
    len = cache ? clen : 0;
    clen = len;
    size = cache ? (BUFIZE - clen) : BUFIZE;
    len = (size < (dlen - rofst)) ? size : (dlen - rofst);
    if (0 < len) {
        memcpy((cbuffer + ofst), (data + rofst), len);
        cache = true;
        cofst = ofst;
        clen += len;
        dofst = rofst;
        rofst += len;

        log_debug("cache2 data (cahce:%d/%d, data:%d/%d)", cofst, clen, dofst, rofst);
        hexdump(cbuffer, clen);

        p0 = cbuffer;
        plen = clen;
        goto check_boundary;
    }

    return 0;
}


int main(int agrc, char *argv[])
{
    FILE *istream, *ostream;
    char buffer[BUFIZE +1];
    size_t rlen, wlen;
    char *prog = basename(argv[0]);
    struct context ctx = {
        .content_boundary = CONTENT_BOUNDARY,
    };

    if (0 == strcmp(prog, "iostream")) {
        printf("Nothing\n");
    } else if (0 == strcmp(prog, "ostream")) {
        istream = fopen(STREAM_BIN, "rb");
        while (!feof(istream)) {
            rlen = fread(buffer, 1, BUFIZE, istream);
            // hexdump(buffer, rlen);
            // printf("read %d(0x%x) data ...\n", rlen, rlen       );
            wlen = fio_input_multipart_form_data(&ctx, buffer, rlen);
        }

    }



    return 0;
}