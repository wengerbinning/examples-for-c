
#### struct flowi_common

```c
struct flowi_common {
	int	flowic_oif;
	int	flowic_iif;
	__u32	flowic_mark;
	__u8	flowic_tos;
	__u8	flowic_scope;
	__u8	flowic_proto;
	__u8	flowic_flags;
#define FLOWI_FLAG_ANYSRC		0x01
#define FLOWI_FLAG_KNOWN_NH		0x02
#define FLOWI_FLAG_SKIP_NH_OIF		0x04
	__u32	flowic_secid;
	kuid_t  flowic_uid;
	struct flowi_tunnel flowic_tun_key;
	__u32		flowic_multipath_hash;
};
```
#### union flowi_uli

```c
union flowi_uli {
	struct {
		__be16	dport;
		__be16	sport;
	} ports;

	struct {
		__u8	type;
		__u8	code;
	} icmpt;

	struct {
		__le16	dport;
		__le16	sport;
	} dnports;

	__be32		spi;
	__be32		gre_key;

	struct {
		__u8	type;
	} mht;
};
```
#### struct flowi4

```c
#define flowi4_oif		__fl_common.flowic_oif
#define flowi4_iif		__fl_common.flowic_iif
#define flowi4_mark		__fl_common.flowic_mark
#define flowi4_tos		__fl_common.flowic_tos
#define flowi4_scope		__fl_common.flowic_scope
#define flowi4_proto		__fl_common.flowic_proto
#define flowi4_flags		__fl_common.flowic_flags
#define flowi4_secid		__fl_common.flowic_secid
#define flowi4_tun_key		__fl_common.flowic_tun_key
#define flowi4_uid		    __fl_common.flowic_uid
#define flowi4_multipath_hash	__fl_common.flowic_multipath_hash

#define fl4_sport		uli.ports.sport
#define fl4_dport		uli.ports.dport
#define fl4_icmp_type	uli.icmpt.type
#define fl4_icmp_code	uli.icmpt.code
#define fl4_ipsec_spi	uli.spi
#define fl4_mh_type		uli.mht.type
#define fl4_gre_key		uli.gre_key

struct flowi4 {
	struct flowi_common	__fl_common;

	/* (saddr,daddr) must be grouped, same order as in IP header */
	__be32			saddr;
	__be32			daddr;

	union flowi_uli		uli;
} __attribute__((__aligned__(BITS_PER_LONG/8)));
```


#### struct rtable

```c
struct rtable {
	struct dst_entry	dst;

	int			rt_genid;
	unsigned int		rt_flags;
	__u16			rt_type;
	__u8			rt_is_input;
	__u8			rt_uses_gateway;

	int			rt_iif;

	u8			rt_gw_family;
	/* Info on neighbour */
	union {
		__be32		rt_gw4;
		struct in6_addr	rt_gw6;
	};

	/* Miscellaneous cached information */
	u32			rt_mtu_locked:1,
				rt_pmtu:31;

	struct list_head	rt_uncached;
	struct uncached_list	*rt_uncached_list;
};

```


## Call Graph

fib_validate_source -> __fib_validate_source

fib_lookup -> fib_table_lookup -> 

ip_route_input_noref -> ip_route_input_rcu
ip_route_input_rcu -> ip_route_input_slow


#### 本机路由

ipv4_sk_update_pmtu -> ip_route_output_flow
ip_route_connect -> ip_route_output_flow

ip_route_output_flow -> __ip_route_output_key
ip_route_output_flow -> xfrm_lookup_route

xfrm_lookup_route -> __ip_route_output_key
xfrm_lookup_route -> xfrm_lookup_route


#### 转发路由

ip_forward -> skb_warn_if_lro
ip_forward -> xfrm4_policy_check
ip_forward -> skb_forward_csum
ip_forward -> xfrm4_route_forward
ip_forward -> NF_HOOK(NFPROTO_IPV4,NF_INET_FORWARD,ip_forward_finish)

ip_forward_finish -> dst_output















ip_route_input_noref -> ip_route_input_common

* ip_route_input_common -> ip_route_input_slow


ip_route_input_noref -> ip_route_input_rcu -> ip_route_input_slow

ip_route_input_slow -> skb_tunnel_info
ip_route_input_slow -> fib4_rules_early_flow_dissect
ip_route_input_slow -> ip_mkroute_input

ip_mkroute_input -> __mkroute_input

__mkroute_input -> rth->dst.input=ip_forward -> skb_dst_set

## LINKS

* <https://megahertz66.github.io/kernel/2020/11/28/Linux-route_subsysytem/>