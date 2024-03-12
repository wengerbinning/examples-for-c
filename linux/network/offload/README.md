

```c
struct xfrm_type {
	char *description;
	struct module *owner;
	u8	proto;
	u8	flags;

#define XFRM_TYPE_NON_FRAGMENT	1
#define XFRM_TYPE_REPLAY_PROT	2
#define XFRM_TYPE_LOCAL_COADDR	4
#define XFRM_TYPE_REMOTE_COADDR	8

	int	    (*init_state) (struct xfrm_state *x);
	void	(*destructor) (struct xfrm_state *);
	int		(*input) (struct xfrm_state *, struct sk_buff *skb);
	int		(*output) (struct xfrm_state *, struct sk_buff *pskb);
	int		(*reject) (struct xfrm_state *, struct sk_buff *, const struct flowi *);
	int	    (*hdr_offset) (struct xfrm_state *, struct sk_buff *, u8 **);
};
```

```c
struct xfrm_type_offload {
	char *description;
	struct module *owner;
	u8 proto;
	void    (*encap) (struct xfrm_state *, struct sk_buff *pskb);
	int		(*input_tail) (struct xfrm_state *x, struct sk_buff *skb);
	int		(*xmit) (struct xfrm_state *, struct sk_buff *pskb, netdev_features_t features);
};

```



flowoffload_tg -> xt_flowoffload_route
flowoffload_tg -> flow_offload_add
flowoffload_tg -> nf_flow_offload_hw_add



__xfrm_init_state

xfrm_get_type_offload

xfrm_dev_offload_ok
xfrm_dev_offload_ok

xfrm_output -> xfrm_dev_offload_ok

x->type_offload


callbacks.gso_segment

xfrm_output_one -> x->type_offload->encap



#### ESP

* esp4_offload - struct net_offload
* esp4_gro_receive
* esp4_gso_segment


* esp_type_offload - struct xfrm_type_offload
* esp_input_tail
* esp_xmit
* esp4_gso_encap

* esp4_offload_init
* esp4_offload_exit




esp4_gro_receive ->
xfrm_offload
xfrm_input




net_rx_action -> __napi_poll -> mtk_napi_rx -> napi_gro_receive

napi_gro_receive -> dev_gro_receive -> inet_gro_receive -> esp4_gro_receive

if (debug_esp4_gro_receive) {
    debug_esp4_gro_receive = false;
    dump_stack();
}