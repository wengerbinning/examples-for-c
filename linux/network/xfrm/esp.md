

#### ESP数据加密

esp_output -> crypto_aead_authsize
esp_output -> esp_output_tail

esp_output_tail -> crypto_aead_authsize
esp_output_tail -> crypto_aead_ivsize
esp_output_tail -> aead_request_set_callback
esp_output_tail -> aead_request_set_crypt
esp_output_tail -> esp_output_restore_header
esp_output_tail -> crypto_aead_encrypt

#### ESP数据解密

esp_input -> esp_input_set_header
esp_input -> aead_request_set_callback
esp_input -> aead_request_set_crypt
esp_input -> crypto_aead_decrypt
esp_input -> esp_input_done2(skb, err);

esp_input_done2 -> esp_remove_trailer
esp_input_done2 -> skb_pull_rcsum
esp_input_done2 -> skb_reset_transport_header
esp_input_done2 -> skb_set_transport_header

esp_input_done -> xfrm_input_resume

## Symbol Table

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