#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define RESULT_FILE "result.txt"
#define BUFIZE 256

#define HEXDUMP_COLUM	16
#define HEXDUMP_CHAR1	' '
#define HEXDUMP_ASCII	true
#define HEXDUMP_CHAR2	' '

static inline bool str2bool(const char *str) {
	if (!str)
		return false;

	if (0 == strcmp(str, "true") || 0 == strcmp(str, "True"))
		return true;

	if (0 == strcmp(str, "yes") || 0 == strcmp(str, "YES"))
		return true;

	if (1 == atoi(str))
		return true;

	return false;
}

void hexdump (const void *ptr, unsigned int size) {
	int i, j;
	unsigned char *buf;
	const char *env;
	char chr1, chr2;
	int col;
	bool ascii;

	if (!ptr)
		return;

	env = getenv("HEXDUMP_COLUM");
	col = env ? atoi(env) : HEXDUMP_COLUM;
	env = getenv("HEXDUMP_CHAR1");
	chr1 = env ? *(char *)env : HEXDUMP_CHAR1;
	env = getenv("HEXDUMP_ASCII");
	ascii = env ? str2bool(env) : HEXDUMP_ASCII;
	env = getenv("HEXDUMP_CHAR2");
	chr2 = env ? *(char *)env : HEXDUMP_CHAR2;

	buf = malloc(col);
	memset(buf, 0, col);

	for (i = 0; i < size; i++) {
		printf("%02X", *(unsigned char *)(ptr + i));
		buf[i % col] = *(unsigned char *)(ptr + i);

		if (((i + 1) % col) || ascii)
			printf("%c", chr1);
		else
			printf("\n");

		if (!((i + 1) % col) && ascii) {
			printf(" | ");
			for (j = 0; j < col; j++) {
				printf("%c", (buf[j] > 31 && buf[j] < 128) ? buf[j] : '.');
				if (j != col - 1)
					printf("%c", chr2);
			}
			memset(buf, 0, col);
			printf ("\n");

		}
	}

	if (size % col) {
		for (i = 0; i < (col - (size % col)); i++) {
			printf("  ");
			if ((i != (col - (size % col) - 1)) || ascii)
				printf("%c", chr1);
		}
		if (ascii) {
			printf(" | ");
			for (j = 0; j < col; j++) {
				printf("%c", (buf[j] > 31 && buf[j] < 127) ? buf[j] : '.');
				if (j != col - 1)
					printf("%c", chr2);
			}
		}
		printf("\n");
	}

	free(buf);
}

#define OVPN_UNKNOWN 0
#define OVPN_CLIENT	1
#define OVPN_ROUTE 2
#define OVPN_STATS 3

int main (int argc, char *argv[]) {
	FILE *file;
	char buffer[BUFIZE + 1];
	int parse = OVPN_UNKNOWN;
	char *ptr, *col1, *col2, *col3, *col4, *col5;




	file = fopen(RESULT_FILE, "r");
	hexdump(buffer, BUFIZE);

	while (!feof(file)) {
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, BUFIZE, file);

		if (!strlen(buffer))
			continue;

		//printf("line: %s", buffer);
		if (0 == strncmp(buffer, "OpenVPN CLIENT LIST", 19)) {
			parse = OVPN_CLIENT;  continue;
		} else if (0 == strncmp(buffer, "ROUTING TABLE", 13)) {
			parse = OVPN_ROUTE;   continue;
		} else if (0 == strncmp(buffer, "GLOBAL STATS", 12)) {
			parse = OVPN_STATS;   continue;
		}

		if (parse == OVPN_UNKNOWN)
			continue;

		ptr = buffer;
		switch (parse) {
			case OVPN_CLIENT:
				col1=ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}

				if (0 == strcmp(col1, "Updated") || 0 == strcmp(col1, "Common Name"))
					continue;

				col2 = ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}
				col3 = ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}
				col4 = ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}
				col5 = ptr;
				if ((ptr = strstr(ptr, "\n")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0';
				}
				printf("column: %s\n", col5);
				break;

			case OVPN_ROUTE:
				col1=ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}

				if (0 == strcmp(col1, "Virtual Address"))
					continue;

				col2 = ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}
				col3 = ptr;
				if ((ptr = strstr(ptr, ",")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0'; ptr = ptr + 1;
				}
				col4 = ptr;
				if ((ptr = strstr(ptr, "\n")) && ptr < (buffer + BUFIZE)) {
					*ptr = '\0';
				}
				printf("column: %s\n", col4);
				break;
			case OVPN_STATS:
				break;
			default:
				printf("Nothing ....\n");
		}

	}

	fclose(file);

	return 0;
}