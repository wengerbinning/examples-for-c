#ifndef __BINARY_H__
#define __BINARY_H__

#define CMP_SET_BITS(a, b)		(~a & (a ^ b))
#define CMP_UNSET_BITS(a, b)	(a & (a ^ b))
#define CMP_SAME_BITS(a, b)		(~(a ^ b))

#define GET_BITS_CHANGES(x, a, b)	\
	x ?	(~a & (a ^ b)) : (a & (a ^ b))	

#define GET_BITS_SAME(x, a, b) 		\
	x ? (a & ~(a ^ b)) : (~a & ~(a ^ b))
	

/* operation: a less than b in the mask range. */
#define CMP_LES_THAN(a, b, mask) ((a & mask) < (b & mask))
/* operation: a equal to b in the mask range. */
#define CMP_EQU(a, b, mask) ((a & mask) == (b & mask))
/*operation:  a greater than b in the mask range. */
#define CMP_GRE_THAN(a, b, mask) ((a & mask) > (b & mask))


#endif /* __BINARY_H__ */
