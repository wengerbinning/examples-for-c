#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Iterate over substrings in a string based on delimiters. 
 *  char sub[] - Save the substring.
 *  unsigned int len - Save the substring's actual length.
 *  char *p, *q - The pointers for traversing substrings.
 *  char *str - The string to br traversed.
 *  char *sep - The separator for traversing. 
 */
/* Warning - sub must not be emoty. */
#define string_for_by_separator(sub, len, p, q, str, sep)	\
for (																		   \
	p = str, q = (p ? strstr(p, sep) : NULL),                                  \
	memset(sub, 0, sizeof(sub)),											   \
	len = (q ? (q - p) : (p ? strlen(p): 0)),			     	     		   \
	len = ((len >= sizeof(sub)) ? (sizeof(sub) - 1) : len),				       \
	memcpy(sub, p, len)											               \
	; p;                                                                       \
	p = (q ? (q + 1) : q), q = (p ? strstr(p, sep) : NULL),			           \
	memset(sub, 0, sizeof(sub)),							                   \
	len = (q ? (q - p) : (p ? strlen(p): 0)),   							   \
	len = ((len >= sizeof(sub)) ? (sizeof(sub) -1) : len),				       \
	memcpy(sub, p, len)														   \
)



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





