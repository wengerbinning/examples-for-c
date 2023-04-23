#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef void * element_hooker(int idx, char *element, void *priv);

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
	char string[] = "port0: port1";
	int cnt;

	cnt = str_for_element(string, sizeof(string), ":", NULL, port_hooker);

	printf("parse %d\n", cnt);
	return 0;
}