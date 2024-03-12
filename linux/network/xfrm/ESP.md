
#### struct ip_esp_hdr

```c
struct ip_esp_hdr {
	__be32 spi;
	__be32 seq_no;		/* Sequence number */
	__u8  enc_data[0];	/* Variable len but >=8. Mind the 64 bit alignment! */
};
```

#### ip_esp_hdr

```c
static inline struct ip_esp_hdr *ip_esp_hdr (const struct sk_buff *skb)
{
	return (struct ip_esp_hdr *)skb_transport_header(skb);
}
```

#### skb_transport_header

```c
static inline unsigned char *skb_transport_header (const struct sk_buff *skb)
{
	return skb->head + skb->transport_header;
}
```


#### skb_mac_header

```c
static inline unsigned char *skb_mac_header (const struct sk_buff *skb)
{
	return skb->head + skb->mac_header;
}
```