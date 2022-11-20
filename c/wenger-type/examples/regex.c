#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <regex.h>


int test_api_regex(const char *const re, const char *const str);


int main (int argc, char *argv[]) {
	test_api_regex("BBC.*", "@A@BBCdew");
	return 0;
}



int test_api_regex(const char *const re, const char *const str) {
	regex_t regex;
	regmatch_t pmatch[1];
	const char *s = str;
	int offset;
	int len;
	
	if (regcomp(&regex, re, REG_NEWLINE))
		return 0;

	for(int i=0; ; i++) {
		if (regexec(&regex, s, 1, pmatch, 0))
			break;
		
		offset = (s - str) + pmatch[0].rm_so;
		len = pmatch[0].rm_eo - pmatch[0].rm_so;
		printf("Found %d substr: %.*s, len %d \n", i, pmatch[0].rm_so, len);

		s += pmatch[0].rm_eo;
	}
	
	return 0;
}

