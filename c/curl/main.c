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

int main(int agrc, char *argv[]) {
    char url[] = "http://10.0.0.10/released/grandstream/GWN/2024-04-02/v0.0/v0.0.0.1/images/prod/gwn7062efw.bin";
    // char url[] = "http://10.0.0.10/debug";
    struct url_t * new_url, *p;

    printf("Start download resource info(%d) from \'%s\' by libcurl ...\n", sizeof(header),  url);

    ret = curl_global_init(CURL_GLOBAL_ALL);

    /* Curl context init */
    
    new_url = url_new(url);

    list_add(&new_url->list, &urls_list);

    list_for_each_entry (p, urls_list, list) {
        printf("url: %s\n", p->url);
    }
    
    /* Curl context exit */

    curl_global_cleanup();

    return 0;
}