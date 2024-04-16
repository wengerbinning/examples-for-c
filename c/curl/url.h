#ifndef __URL_H__
#define __URL_H__

#include "list.h"

struct url_t {
    struct list_head list;
    char *url;
    unsigned int flags;

#define URLF_VALID   (0x01 << 0)
#define URLF_RANGE   (0x01 << 1)
#define URLF_HTTP    (0x01 << 2)
#define URLF_HTTPS   (0x01 << 3)
#define URLF_FTP     (0x01 << 4)
#define URLF_TFTP    (0x01 << 5)
#define URLF_FILE    (0x01 << 6)
};


struct url_t * url_new (char *url);
void url_free (struct url_t * url);

int url_check (struct url_t * url);

#endif /** __URL_H__ /