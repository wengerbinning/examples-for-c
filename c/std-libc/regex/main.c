#include <stdio.h>
#include <regex.h>


int main (int argc, char *argv[]) {
    char *str, *pattern;
    regex_t regex;
    size_t nmatch = 3;
    regmatch_t pmatch[3];

    if (!argv[1] && !argv[2])
        return 0;

    pattern = argv[1];
    str = argv[2];

    regcomp(&regex, pattern, REG_EXTENDED);
    if (0 == regexec(&regex, str, nmatch, pmatch, 0)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    regfree(&regex);

    return 0;
}