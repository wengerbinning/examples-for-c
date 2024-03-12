

#### xfrm_offload

```c
static inline struct xfrm_offload *xfrm_offload (struct sk_buff *skb)
{
#ifdef CONFIG_XFRM
	struct sec_path *sp = skb_sec_path(skb);

	if (!sp || !sp->olen || sp->len != sp->olen)
		return NULL;

	return &sp->ovec[sp->olen - 1];
#else
	return NULL;
#endif
}
```

#### skb_ext_find

```c
static inline void *skb_ext_find(const struct sk_buff *skb, enum skb_ext_id id)
{
	if (skb_ext_exist(skb, id)) {
		struct skb_ext *ext = skb->extensions;

		return (void *)ext + (ext->offset[id] << 3);
	}

	return NULL;
}
```

#### skb_sec_path

```c
static inline struct sec_path *skb_sec_path(const struct sk_buff *skb)
{
#ifdef CONFIG_XFRM
	return skb_ext_find(skb, SKB_EXT_SEC_PATH);
#else
	return NULL;
#endif
}
```

## d

