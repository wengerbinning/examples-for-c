#ifndef __W_STRING_H__
#define __W_STRING_H__





extern int string_escape (const char *str, char chr, char *buffer, size_t bufsize);

#endif /* __W_STRING_H__*/


	len = (q ? (q - p) : strlen(str)),											\
	len = ((len > sizeof(sub)) ? sizeof(sub) : len),							\
	strncpy(sub, str, len)														\