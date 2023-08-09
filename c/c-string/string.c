#include <stdio.h>
#include <string.h>
#include <stdlib.h>





int main(int argc, char *argv[]) {
	char *str = "portdewdwedwedsdsad`0, port1,port2,port3,port5,prt2,1234567890abcdee,abcdefghijklmnopqrstuvwxyz,dqwdqwdqwdqwd,qwedqwdqdqwdqwdqdwqwdqwdqwdqwd,dqwdqwdqwdqwdqwdqwdwq";
	char buffer[16];
	char *p, *q;
	int len;

	printf("%p %d, %d\n", str, strlen(str), sizeof(buffer));
	string_for_by_separator
	 (buffer, len, p, q, str, ":") {
		printf("%p %08p\t", p, (q ? q : 0));
		printf("size %d: |%s|", len, buffer);
		printf("\n");
	}


	return 0;

}





