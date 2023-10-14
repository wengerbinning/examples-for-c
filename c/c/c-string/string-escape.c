#include <stdio.h>
#include <string.h>

#define memcpy(q, p, size) \
    do {                                                                            \
        printf("(%s, line: %d) %p -> %p, %d\n", __func__, __LINE__, p, q, size);    \
        memcpy(q, p, size);                                                         \
    } while (0)





int string_escape (const char *str, char chr, char *buffer, size_t bufsize)
{
    int cnt = 0;
    const char *p, *c;
    char *q;
    int len, offset = 0;

    if (!buffer)
        return -1;
    
    p = str;
    q = buffer;
    memset(buffer, 0, bufsize);

    while (( c = memchr(p, chr, (str + strlen(str) - p)) )) {
        cnt++;
        len = c - p;

        if (((bufsize - 1) - offset) <= 0) {
            *(buffer + (bufsize - 1)) = '\0';
            break;
        }

        if ((len) >= ((bufsize - 1) - offset)) {
            memcpy(q, p, ((bufsize - 1) - offset));
            *(buffer + (bufsize - 1)) = '\0';
            q += (bufsize - 1) - offset;
            offset = bufsize - 1;
            break;
        }

        if (len > 0)
            memcpy(q, p, len);

        if (((bufsize - 1) - offset - len) < 2) {
            *(q + len + 0) = '\0';
            q += 1;
            offset += 1;
            break;
        }

        *(q + len + 0) = '\\';
        *(q + len + 1) = chr;
        q += len + 2;
        offset += len + 2;
   
        p  = c + 1;
    }

    if (((str + strlen(str) - p) > 0) && (((buffer + bufsize - 1) - q) > 0)) {
        if ((str + strlen(str) - p) >= ((buffer + bufsize - 1) - q)) {
            memcpy(q, p, ((buffer + bufsize - 1) - q));
            *(buffer + bufsize - 1) = '\0';
        } else {
            memcpy(q, p, (str + strlen(str) - p));
            *(q + (str + strlen(str) - p)) = '\0';
        }
    }

    return cnt;
}