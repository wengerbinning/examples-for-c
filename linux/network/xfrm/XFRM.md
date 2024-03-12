

#### struct xfrm_offload

```c
struct xfrm_offload {
	/* Output sequence number for replay protection on offloading. */
	struct {
		__u32 low;
		__u32 hi;
	} seq;

	__u32			flags;
#define	SA_DELETE_REQ		1
#define	CRYPTO_DONE		2
#define	CRYPTO_NEXT_DONE	4
#define	CRYPTO_FALLBACK		8
#define	XFRM_GSO_SEGMENT	16
#define	XFRM_GRO		32
#define	XFRM_ESP_NO_TRAILER	64
#define	XFRM_DEV_RESUME		128
#define	XFRM_XMIT		256

	__u32			status;
#define CRYPTO_SUCCESS				1
#define CRYPTO_GENERIC_ERROR			2
#define CRYPTO_TRANSPORT_AH_AUTH_FAILED		4
#define CRYPTO_TRANSPORT_ESP_AUTH_FAILED	8
#define CRYPTO_TUNNEL_AH_AUTH_FAILED		16
#define CRYPTO_TUNNEL_ESP_AUTH_FAILED		32
#define CRYPTO_INVALID_PACKET_SYNTAX		64
#define CRYPTO_INVALID_PROTOCOL			128

	__u8			proto;
};
```


#### struct sec_path

```c
struct sec_path {
	int			len;
	int			olen;

	struct xfrm_state	*xvec[XFRM_MAX_DEPTH];
	struct xfrm_offload	ovec[XFRM_MAX_OFFLOAD_DEPTH];
};
```