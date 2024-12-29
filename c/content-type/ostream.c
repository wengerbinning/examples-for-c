#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <libgen.h>
#include <unistd.h>

#include "hexdump.h"
#include "iostream.h"


#define BUFIZE 256



#define log_error(fmt, ...)     printf("\033[31m" fmt "\033[0m\n", ##  __VA_ARGS__ )
#define log_warning(fmt, ...)   printf("\033[33m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_notice(fmt, ...)    printf("\033[32m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_info(fmt, ...)      printf("\033[37m" fmt "\033[0m\n", ## __VA_ARGS__ )
#define log_debug(fmt, ...)     printf("\033[34m" fmt "\033[0m\n", ## __VA_ARGS__ )




size_t form_write(struct context *ctx, struct form *form, char *buf, size_t len)
{
    form->index = ctx->form_count;
    // log_debug("%d offset:%d, %s", ctx->form_count, form->offset, buf);

    if (form->offset == 0 && form->end) {
        printf("[%02d] %s\n", form->index, buf);
    } else {
        snprintf(form->buffer + form->offset, FORM_BUFZIE - form->offset, "%s", buf);
        if ( form->end )
            printf("[%02d] %s\n", form->index, form->buffer);
    }

    return len;
}

int form_finish (struct context *ctx, struct form *form) {
    if (form->end) {
        printf("[%02d] %s\n", form->index, form->buffer);
    }
    return 0;
}

struct form _form_static;

// ============================================================================
static int
fio_input_multipart_form_data(
    struct context *ctx,
    char *data, size_t dlen
)
// ============================================================================
{
    char *boundary, *p0, *p1;
    size_t dofst = 0, rofst = 0;
    size_t ofst, size, len, cofst, plen;
    char buffer[BUFIZE + 1];
    static int idx = 0;
    static bool cache = false;
    static size_t clen = 0;
    static char cbuffer[BUFIZE + 1];
    boundary = ctx->content_boundary;
    struct form *form = &_form_static;

    // log_warning("read %d(0x%x) data ...", dlen, dlen);
    // hexdump(data, dlen);

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

        // log_debug("cache0 data (cache:%d/%d, data:%d/%d)", cofst, clen, dofst, rofst);
        // hexdump(cbuffer, clen);

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
            memset(p1 - 4, 0, 4);
            size -= 4;
        } else if ( (2 <= size) && 0 == strncmp(p1 - 2, "--", 2) ) {
            /* first data */
            log_notice("==== START ====");
            size -= 2;
            idx = 1;
            ctx->form_count = idx;
            form->offset = 0;
        }

        /* write form data end */
        if ( 0 < size ) {
            ctx->form_count = idx++;
            form->end = true;
            // log_notice("index: %d, cache:%s => %d:%s", ctx->form_count,
            //     cache ? "true" : "false", strlen(p0), p0);
            // hexdump(p0, size);
            form_write(ctx, form, p0, size);

        }

        /* next form */
        form->offset = 0;
        form->end = false;
        p0 = p1 + strlen(boundary);
        plen -= strlen(boundary);

        if (plen == 4 && 0 == strncmp(p0, "--\r\n", 4)) {
            form_finish(ctx, form);
            log_notice("==== END1 ====");
            return 0;
        } else if (2 <= plen && 0 == strncmp(p0, "\r\n", 2)) {
            /* skip boundary suffix: \r\n */
            p0 += 2;
            plen -= 2;
            suffix = true;
        }

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

            // log_debug("update1 cache (%d/%d, %d/%d)", cofst, clen, dofst, rofst);
            // hexdump(cbuffer, clen);

            /* update pointer */
            p0 = cbuffer;
            plen = clen;
        /* */
        } else if (cache) {
            dofst += p0 - (cbuffer + cofst);
            p0 = data + dofst;
            plen = dlen - dofst;
            /* skip boundary suffix: \r\n */
            if (plen == 4 && 0 == strncmp(p0, "--\r\n", 4)) {
                form_finish(ctx, form);
                log_notice("==== END2 ====");
                return 0;
            } else if (2 <= plen && 0 == strncmp(p0, "\r\n", 2)) {
                p0 += 2;
                plen -= 2;
                dofst += 2;
                suffix = true;
            }
            cache = false;
            rofst = dofst;

            // log_debug("change1 cache to data 0x%x/0x%x len:%d", dofst, rofst, plen);
            // hexdump(p0, plen);
        }

        /* */
       if (!cache) {
            dofst = p0 - data;
            rofst = dofst;
        }
        if (!cache && !suffix) {
            len = plen + strlen(boundary);
            memcpy(cbuffer, (p0 - strlen(boundary)), len);
            cache = true;
            cofst = 0;
            clen = len;
            rofst += plen;

            // log_debug("cahce1 cache:%d/%d, data:%d/%d", cofst, clen, dofst, rofst);
            // hexdump(cbuffer, clen);
        }

    }


    /* check end */
    p0 = cache ? cbuffer : (data + dofst);
    plen = cache ? clen : (dlen - dofst);
    if ( plen == 4 && 0 == strncmp(p0, "--\r\n", 4) ) {
        log_notice("==== END2 ====");
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
        if (form->offset == 0) {
            ctx->form_count++;
        }
        form->end = false;
        // log_notice("#index: %d, cache:%s => %d:%s", ctx->form_count + 1,
        //     cache ? "true" : "false", strlen(buffer), buffer);
        // hexdump( buffer, len );
        form_write(ctx, form, buffer, len);

        /* */
        form->offset += len;
        cache = false;
        if (cofst < len) {
            dofst = len - cofst;
            rofst = dofst;
            p0 = data + dofst;
            plen = dlen - dofst;

            // log_debug("change2 cahce to data (data:%d/%d)", dofst, rofst);
            // hexdump(p0, plen);

        } else if ( size <= BUFIZE ) {
            ofst = clen - size;
            memcpy(buffer, cbuffer + ofst, size);
            memcpy(cbuffer, buffer, size);
            cache = true;
            cofst -= len;
            clen = size;

            // log_debug("update2 cache (cahce:%d/%d, data:%d/%d)", cofst, clen, dofst, rofst);
            // hexdump(cbuffer, clen);

            p0 = cbuffer;
            plen = clen;
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

        // log_debug("cache2 data (cahce:%d/%d, data:%d/%d) %d", cofst, clen, dofst, rofst, len);
        // hexdump(cbuffer, clen);

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

            wlen = fio_input_multipart_form_data(&ctx, buffer, rlen);
        }

    }



    return 0;
}