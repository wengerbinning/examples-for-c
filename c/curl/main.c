#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <curl/curl.h>

#include "url.h"
#include "list.h"

#define HEADER_BLOCK_SIZE   0x200
#define MAX_PACK_IMAGE 4
#define MAX_CNAME 64


// int main(int agrc, char *argv[]) {
//     CURL *curl = curl_easy_init();

//     /** Setting Curl Options */
//     curl_easy_setopt(curl, CURLOPT_URL, url->url);
//     /** Send Request */
//     if ((ret = curl_easy_perform(curl) != CURLE_OK)) {
//         return 0;
//     }

//     curl_easy_cleanup(curl);

//     return 0;
// }


size_t read_callback(char *buffer, size_t size, size_t nitems, void *priv)
{
    FILE *in = (FILE *)priv;
    size_t bytes_read;

    /* I'm doing it this way to get closer to what the reporter is doing.
     Technically we don't need to do this, we could just use the default read
     callback which is fread. Also, 'size' param is always set to 1 by libcurl
     so it's fine to pass as buffer, size, nitems, instream. */
    printf("start read data ...\n");
    bytes_read = fread(buffer, 1, 16, (FILE *)in);
    printf("read %d data\n", bytes_read);

  return bytes_read;
}

#define   B  (1)
#define KiB  (1 * 1024)
#define MiB  (1 * 1024 * 1024)
#define GiB  (1 * 1024 * 1024 * 1024)
#define MEM_SIZE(n, unit) ((n) * (unit))

int main(int agrc, char *argv[]) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();


    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/api/cgi1");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)MEM_SIZE(128, B));
    curl_easy_setopt(curl, CURLOPT_READDATA, (void *)stdin);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);


    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    curl_global_cleanup();

    return 0;
}