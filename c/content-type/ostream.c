#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <libgen.h>
#include <unistd.h>

#include "hexdump.h"
#include "iostream.h"


#define BUFIZE 32



#define log_error(fmt, ...)     printf("\033[31m" fmt "\033[0m\n", ##  __VA_ARGS__ )
#define log_warning(fmt, ...)   printf("\033[33m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_notice(fmt, ...)    printf("\033[32m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_info(fmt, ...)      printf("\033[37m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_debug(fmt, ...)     printf("\033[34m" fmt "\033[0m\n", ## __VA_ARGS__ )



// ============================================================================
static int
fio_input_multipart_form_data(
    struct context *ctx,
    char *data, size_t dlen
)
// ============================================================================
{
    char *p0, *p1;
    size_t ofst, size, len;
    size_t cofst, dofst, rofst, plen;
    char *boundary;
    char buffer[BUFIZE + 1];
    static bool start;
    static int idx = 0;
    static bool cache = false;
    static size_t clen = 0      ;
    static char cbuffer[BUFIZE + 1];


    boundary = ctx->content_boundary;

    log_warning("read %d(0x%x) data ...", dlen, dlen);
    hexdump(data, dlen);

    /* check cache */

    // 如果存在cache, 则记录clen的位置;
    // 复制一部分数据到cache
    // 记录复制的数据偏移dofst
    p0 = data;
    plen = dlen;
    dofst = 0;
    rofst = 0;
    if ( cache ) {
        cofst = clen;

        log_debug("found cache");
        hexdump(cbuffer, clen);

        len = (dlen < (BUFIZE - clen)) ? dlen : (BUFIZE - clen);
        memcpy(cbuffer + cofst, data, len);
        clen += len;
        p0 = cbuffer;
        plen = clen;
        rofst = len;
    }

    log_debug("dofst: 0x%x,  rofst: 0x%x", dofst, rofst);

    /* check boundary */
    check_boundary:
    if (cache) {
        log_debug("check in cache: %d/%d %p/%d %p/%d %s", cofst, clen, data, dofst, p0, plen, boundary);
        hexdump(p0, plen);
    } else {
        log_debug("check in data: %p/%d %p/%d %s", data, dofst, p0, plen, boundary);
    }
    while ( (p1 = (char *)memmem(p0, plen, boundary, strlen(boundary))) ) {
        bool suffix = false;
        size  = p1 - p0;
        plen -= size;

        if ((4 <= size) && (0 == strncmp(p1 - 4, "\r\n--", 4))) {
            memset(p1 - 4, 0, 2);
            size -= 4;
        } else if ( (2 <= size) && 0 == strncmp(p1 - 2, "--", 2) ) {
            /* first data */
            log_notice("==== START ====");
            size -= 2;
            idx = 1;
        }

        /* write form data end */
        if ( 0 < size ) {
            log_notice("index: %d, start: %5s, cache: %5s => %s", idx++,
                start ? "true" : "false",
                cache ? "true" : "false",
                p0);
            // hexdump(p0, size);
        }

        /* next form */
        start = true;
        p0 = p1 + strlen(boundary);
        plen -= strlen(boundary);

        if (plen == 4 && 0 == strncmp(p0, "--\r\n", 4)) {
            log_notice("==== END ====");
            return 0;
        } else if (2 < plen && 0 == strncmp(p0, "\r\n", 2)) {
            /* skip boundary suffix: \r\n */
            p0 += 2;
            plen -= 2;
            suffix = true;
        }

        // printf("@@@@@ start: %s, cache: %s\n",
        //     start ? "true" : "false",
        //     cache ? "true" : "false");
        // hexdump(p0, plen);


        // if (cache) {
        //     printf("%d/%d/%d  %d\n", p0 - cbuffer, cofst, clen, dofst);
        // }

        /* update pointer */
        if (cache && (p0 < (cbuffer + cofst))) {
            cofst = (cbuffer + cofst) - p0;
            len = (cbuffer + clen) - p0;
            memcpy(buffer, p0, len);
            memcpy(cbuffer, buffer, len);
            cache = true;
            clen = len;

            size = BUFIZE - clen;
            /* copy data */
            len = ((dlen - dofst) < size) ? ((dlen - dofst)) : size;
            memcpy(cbuffer + clen, (data + dofst), len);
            clen += len;
            /* update pointer */
            p0 = cbuffer;
            plen = clen;
        } else if (cache) {

            ofst = p0 - (cbuffer + cofst);
            dofst += ofst;
            p0 = data + (dofst);
            plen = dlen - (dofst);
            cache = false;

            if (2 < plen && 0 == strncmp(p0, "\r\n", 2)) {
                /* skip boundary suffix: \r\n */
                p0 += 2;
                plen -= 2;
                suffix = true;
            }
            log_debug("change cache to data 0x%x/0x%x", dofst, ofst);
        }

        /* */
        if ( !cache && plen <= 2 ) {
            len = plen + strlen(boundary);
            len += suffix ? 2 : 0; // FIXME - suffix: /r/n
            log_debug("cache1 data %d/%d/%d", len, plen, strlen(boundary));
            hexdump(p1, len);
            memcpy(cbuffer, p1, len);
            cache = true;
            clen = len;
            return 0;
        } else if (!cache) {
            dofst = p0 - data;
            rofst = dofst;
        }

        // printf("offset:0x%04x, size:%d, len:%d\n", dofst, size, plen);

    }

    /* check end */
    p0 = cache ? cbuffer : (data + dofst);
    plen = cache ? clen : (dlen - dofst);
    if ( plen == 4 && 0 == strncmp(p0, "--\r\n", 4) ) {
        log_notice("==== END ====");
        return 0;
    } else if (0 < plen) {
        // hexdump(p0, plen);
    }

    /* update cache */

    if ( cache && BUFIZE <= clen ) {
        // printf("update cache 2\n");
        // hexdump(cbuffer, clen);

        // cache = false;

        len = clen;
        size = strlen(boundary) + 4 + 3;
        if ( size <= BUFIZE ) {
            len -= size;
        }

        /* */
        // if (start)
        //     idx++;

        memcpy(buffer, cbuffer, len);
        log_notice("#index: %d, start: %5s, cache: %5s => %s", idx,
                start ? "true" : "false",
                cache ? "true" : "false",
                buffer);
        // log_debug("demo");
        hexdump( buffer, len );
        // if ( form_data_write(&form, cbuffer, clen) != clen ) {
        //     form_data_exit( &form );
        //     ret = ctx->retVal;
        //     // Log(LOG_DEBUG, "return code %d", ret);
        //     goto exit0;
        // }
        start = false;

        /* */
        cache = false;
        size = strlen(boundary) + 4 + 3;
        if ( size <= BUFIZE ) {
            len = size;
            ofst = clen - len;
            memcpy(buffer, cbuffer + ofst, len);
            memcpy(cbuffer, buffer, len);
            cache = true;
            clen = len;

            log_debug("cache2 data %d/%ld", cofst, clen);
            hexdump(cbuffer + ofst, len);

            p0 = cbuffer;
            plen = clen;
            // goto check_boundary;
        }
        cofst = clen;
    }

    /* cache data */
    // printf("dofst: %d,  rofst: %d\n", dofst, rofst);

    cofst = cache ? clen : 0;
    size = cache ? BUFIZE - cofst : BUFIZE;
    len = (size < (dlen - rofst)) ? size : (dlen - rofst);
    if (0 < len) {
        memcpy((cbuffer + cofst), (data + rofst), len);
        cache = true;
        clen = cofst + len;

        log_debug("cache3 data %d/%ld", cofst, clen);
        hexdump(data + rofst, len);
        dofst = rofst;
        rofst += len;

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