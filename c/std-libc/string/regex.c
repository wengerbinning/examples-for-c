#include <stdio.h>
#include <regex.h>


int main (int argc, char *argv[]) {
                                                                                                                                                                                                                                        regex_t regex;
                                                                                                                                                                                                                                        size_t nmatch = 4;
                                                                                                                                                                                                                                        regmatch_t pmatch[4];


    if (!argv[1] || !argv[2])
        return 0;


    regcomp(&regex, argv[1], REG_EXTENDED);
    for (int i = 2; i < argc; i++) {
        if (0 == regexec(&regex, argv[i], nmatch, pmatch, 0)) {
            printf("%d YES\n", i);
        } else {
            printf("%d NO\n", i);
        }
    }
    regfree(&regex);
    return 0;
}