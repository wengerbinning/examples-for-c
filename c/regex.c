#include <stdio.h>
#include <regex.h>
#include <string.h>

#define BUFIZE 1024

int main (int argc, char *argv[]) {
    // char buffer[BUFIZE + 1] = "Content-Disposition: form-data; name=\"action\"\r\n\r\nupload_check_firmware";
    char buffer[BUFIZE + 1] = "Content-Disposition: form-data; name=\"filename\"; filename=\"firmware.bin\"\r\n\r\nContent-Type: application/octet-stream";

    char *p, *q;
    regex_t regex;
    size_t nmatch = 2;
    regmatch_t pmatch[2];
    char *a, *b, *c, *d;
    p = buffer;
    //
    regcomp(&regex, "[Cc]ontent-[Dd]isposition: ([a-zA-Z\\-]*)", REG_EXTENDED);
    if (0 == regexec(&regex, p, nmatch, pmatch, 0)) {
        a = p + pmatch[1].rm_so;
        q = strstr(a, "\r\n\r\n");
        *(p + pmatch[1].rm_eo) = '\0';
        if (q && q == p + pmatch[0].rm_eo)
            p += pmatch[0].rm_eo + 4;
        else
            p += pmatch[0].rm_eo + 1;

        printf("Content-Disposition = %s => start %d, end %d\n", a,  pmatch[1].rm_so, pmatch[1].rm_eo);
    }
    regfree(&regex);

    //
    regcomp(&regex, "[Nn]ame=\"([a-zA-Z\\-]*)\"", REG_EXTENDED);
    if (0 == regexec(&regex, p, nmatch, pmatch, 0)) {
        printf("Find match\n");
        b = p + pmatch[1].rm_so;
        q = strstr(b, "\r\n\r\n");
        *(p + pmatch[1].rm_eo) = '\0';
        if (q && q == p + pmatch[0].rm_eo)
            p += pmatch[0].rm_eo + 4;
        else
            p += pmatch[0].rm_eo + 1;

        printf("name = %s => start %d, end %d\n", b, pmatch[1].rm_so, pmatch[1].rm_eo);
    }
    regfree(&regex);

    regcomp(&regex, "[Ff]ilename=\"([a-zA-Z\\-\\.]*)\"", REG_EXTENDED);
    if (0 == regexec(&regex, p, nmatch, pmatch, 0)) {
        printf("Find match\n");
        c = p + pmatch[1].rm_so;
        q = strstr(c, "\r\n\r\n");
        *(p + pmatch[1].rm_eo) = '\0';
        if (q && q == p + pmatch[0].rm_eo)
            p += pmatch[0].rm_eo + 4;
        else
            p += pmatch[0].rm_eo + 1;

        printf("filename = %s => start %d, end %d\n", c, pmatch[1].rm_so, pmatch[1].rm_eo);
    }
    regfree(&regex);


    if (strlen(b) == 8  && 0 == strcmp(b, "filename")) {
        printf("str: %s", p);
        regcomp(&regex, "Content-Type: ([a-zA-Z\\/-]*)", REG_EXTENDED);
        if (0 == regexec(&regex, p, nmatch, pmatch, 0)) {
            printf("Find match\n");
            d = p + pmatch[1].rm_so;
            q = strstr(b, "\r\n\r\n");
            *(p + pmatch[1].rm_eo) = '\0';
            if (q && q == p + pmatch[0].rm_eo)
                p += pmatch[0].rm_eo + 4;
            else
                p += pmatch[0].rm_eo + 1;

            printf("Content-Type = %s => start %d, end %d\n", d, pmatch[1].rm_so, pmatch[1].rm_eo);
        }
        regfree(&regex);

    } else
        printf("val: %s", p);







    return 0;
}