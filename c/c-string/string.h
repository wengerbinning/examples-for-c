#ifndef __STRING_H__
#define __STRING_H__

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


extern int string_escape (const char *str, char chr, char *buffer, size_t bufsize);

#endif /* __STRING_H__*/
