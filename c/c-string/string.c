#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string.h"

typedef void *(*element_hooker) (int idx, char *element, void *priv);

int str_for_element(char *string, unsigned int size, char *segment, void *priv, element_hooker hooker) {
	void *sptr, *eptr;
	char buffer[16];

	int idx = 0, len;

	sptr = string;
	
	do {
		while (*(char *)sptr == ' ') 
			sptr++;

		eptr = strstr(sptr, segment);
		
		if (eptr) {
			len = eptr - sptr;
		} else {
			len = size;
		}	
	
		if (len >= sizeof(buffer)) {
			len = sizeof(buffer) - 1;
		}

		strncpy(buffer, sptr, len);

		hooker(idx++, buffer, priv);

		if (eptr) {
			sptr = eptr + 1;
		}

	} while (sptr && eptr);
		
	return idx;
}


void *port_hooker(int idx, char *port, void *priv) {
	printf("%d %s\n", idx, port);
}



int main(int argc, char *argv[]) {
	char *str = "\"12345678\"abcdefgh\"ABCDEFGHJ\"34243242";
	char buffer[100];
	int ret;

	printf(" escape before string: |%s| \n", str);

	ret = string_escape(str, '\"', buffer, sizeof(buffer));

	printf(" escape after string: |%s|, found %d \n", buffer, ret);

	return 0;

}