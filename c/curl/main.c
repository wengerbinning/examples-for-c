#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>

#include "url.h"
#include "list.h"

#define HEADER_BLOCK_SIZE   0x200
#define MAX_PACK_IMAGE 4
#define MAX_CNAME 64

struct firmware_header {
    unsigned int Signature;
    char Name[MAX_PACK_IMAGE][MAX_CNAME];
    unsigned int Size[MAX_PACK_IMAGE];
    unsigned int Version[MAX_PACK_IMAGE];
    unsigned short supported_bits[4];
    unsigned short FwVerMask;
    unsigned short reserved[8041];
};



static size_t curl_func_write (void *ptr, size_t size, size_t nmemb, void *stream)
{
    printf("pr=%p, size=%d, nmemb=%d, stream=%p\n", ptr, size, nmemb, stream);
    printf("data:\n%s\n", ptr);

    return nmemb;
}

int curl_func_progress (void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    return 0;
}





LIST_HEAD(urls_list);
unsigned urls_counter;





int register_url (char *name, char *url) {
    struct url_t *new_url;

    new_url = url_new(url);

    if (name)
        strncpy(new_url->name, name, URL_MAXNAME);

    new_url->id = urls_counter++;

    list_add_tail(&new_url->list, &urls_list);

    return new_url->id;
}

void unregister_url (struct url_t *url) {
    list_del(&url->list);
    url_free(url);
}

int main(int agrc, char *argv[]) {
    char *urls[] = {
        "http://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.1/images/prod/gwn7062efw.bin",
        "https://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.1/images/prod/gwn7062efw.bin",
        "tftp://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.1/images/prod/gwn7062efw.bin",
        "ftp://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.1/images/prod/gwn7062efw.bin",
        "http://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.2/images/prod/gwn7062efw.bin",
        "http://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.1/images/prod/gwn7062efw.bin",
        "http://10.0.0.10/debug",
        NULL
    };

    struct url_t *p, *n;
    struct list_head *list,*next;
    struct firmware_header header;
    int ret, i;
    char *url;

    printf("Start download resource info(%d) by libcurl ...\n", sizeof(header));

    ret = curl_global_init(CURL_GLOBAL_ALL);

    /* Curl context init */

    for (i=0, url=urls[i++]; url != NULL; url=url=urls[i++]) {
        printf("%d, %s\n", i, url);
        register_url(NULL, url);
    }


    list_for_each_entry_safe (p, n, &urls_list, list) {
        url_check(p);

        printf("%p: id=%d, flags=0x%04X, url=%s\n", p, p->id, p->flags, p->url);

        if (p->flags == 0x0600)
            unregister_url(p);
    }


    list_for_each_prev_safe(list, next, &urls_list) {
        p = list_entry(list, struct url_t, list);
        unregister_url(p);
    }

    printf("urls_list is empty: %s\n", list_empty(&urls_list) ? "yes": "no");

    /* Curl context exit */

    curl_global_cleanup();

    return 0;
}