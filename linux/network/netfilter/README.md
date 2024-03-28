

#### struct nf_conn

```c
struct nf_conn {
	/* Usage count in here is 1 for hash table, 1 per skb,
	 * plus 1 for any connection(s) we are `master' for
	 *
	 * Hint, SKB address this struct and refcnt via skb->_nfct and
	 * helpers nf_conntrack_get() and nf_conntrack_put().
	 * Helper nf_ct_put() equals nf_conntrack_put() by dec refcnt,
	 * beware nf_ct_get() is different and don't inc refcnt.
	 */
	struct nf_conntrack ct_general;

	spinlock_t	lock;

	/* jiffies32 when this ct is considered dead */
	u32 timeout;

#ifdef CONFIG_NF_CONNTRACK_ZONES
	struct nf_conntrack_zone zone;
#endif

	/* XXX should I move this to the tail ? - Y.K */
	/* These are my tuples; original and reply */
	struct nf_conntrack_tuple_hash tuplehash[IP_CT_DIR_MAX];

	/* Have we seen traffic both ways yet? (bitset) */
	unsigned long status;

	u16		cpu;
	possible_net_t ct_net;

#if IS_ENABLED(CONFIG_NF_NAT)
	struct hlist_node	nat_bysource;
#endif

	/* all members below initialized via memset */
	struct { } __nfct_init_offset;

	/* If we were expected by an expectation, this will be it */
	struct nf_conn *master;

#if defined(CONFIG_NF_CONNTRACK_MARK)
	u_int32_t mark;
#endif

#ifdef CONFIG_NF_CONNTRACK_SECMARK
	u_int32_t secmark;
#endif

	/* Extensions */
	struct nf_ct_ext *ext;

	/* Storage reserved for other modules, must be the last member */
	union nf_conntrack_proto proto;
};
```


#### struct nf_conntrack_tuple_hash

```c
struct nf_conntrack_tuple_hash {
	struct hlist_nulls_node hnnode;
	struct nf_conntrack_tuple tuple;
};
```

#### struct nf_conntrack_tuple 

```c
struct nf_conntrack_tuple {
	struct nf_conntrack_man src;

	/* These are the parts of the tuple which are fixed. */
	struct {
		union nf_inet_addr u3;
		union {
			/* Add other protocols here. */
			__be16 all;

			struct {
				__be16 port;
			} tcp;
			struct {
				__be16 port;
			} udp;
			struct {
				u_int8_t type, code;
			} icmp;
			struct {
				__be16 port;
			} dccp;
			struct {
				__be16 port;
			} sctp;
			struct {
				__be16 key;
			} gre;
		} u;

		/* The protocol. */
		u_int8_t protonum;

		/* The direction (for tuplehash) */
		u_int8_t dir;
	} dst;
};
```

#### struct nf_conntrack_man

```c
struct nf_conntrack_man {
	union nf_inet_addr u3;
	union nf_conntrack_man_proto u;
	/* Layer 3 protocol */
	u_int16_t l3num;
};
```

#### union nf_inet_addr

```c
union nf_inet_addr {
	__u32		all[4];
	__be32		ip;
	__be32		ip6[4];
	struct in_addr	in;
	struct in6_addr	in6;
};
```

#### enum ip_conntrack_dir

```c
enum ip_conntrack_dir {
	IP_CT_DIR_ORIGINAL,
	IP_CT_DIR_REPLY,
	IP_CT_DIR_MAX
};
```


#### enum ip_conntrack_status

```c
enum ip_conntrack_status {
	/* It's an expected connection: bit 0 set.  This bit never changed */
	IPS_EXPECTED_BIT = 0,
	IPS_EXPECTED = (1 << IPS_EXPECTED_BIT),

	/* We've seen packets both ways: bit 1 set.  Can be set, not unset. */
	IPS_SEEN_REPLY_BIT = 1,
	IPS_SEEN_REPLY = (1 << IPS_SEEN_REPLY_BIT),

	/* Conntrack should never be early-expired. */
	IPS_ASSURED_BIT = 2,
	IPS_ASSURED = (1 << IPS_ASSURED_BIT),

	/* Connection is confirmed: originating packet has left box */
	IPS_CONFIRMED_BIT = 3,
	IPS_CONFIRMED = (1 << IPS_CONFIRMED_BIT),

	/* Connection needs src nat in orig dir.  This bit never changed. */
	IPS_SRC_NAT_BIT = 4,
	IPS_SRC_NAT = (1 << IPS_SRC_NAT_BIT),

	/* Connection needs dst nat in orig dir.  This bit never changed. */
	IPS_DST_NAT_BIT = 5,
	IPS_DST_NAT = (1 << IPS_DST_NAT_BIT),

	/* Both together. */
	IPS_NAT_MASK = (IPS_DST_NAT | IPS_SRC_NAT),

	/* Connection needs TCP sequence adjusted. */
	IPS_SEQ_ADJUST_BIT = 6,
	IPS_SEQ_ADJUST = (1 << IPS_SEQ_ADJUST_BIT),

	/* NAT initialization bits. */
	IPS_SRC_NAT_DONE_BIT = 7,
	IPS_SRC_NAT_DONE = (1 << IPS_SRC_NAT_DONE_BIT),

	IPS_DST_NAT_DONE_BIT = 8,
	IPS_DST_NAT_DONE = (1 << IPS_DST_NAT_DONE_BIT),

	/* Both together */
	IPS_NAT_DONE_MASK = (IPS_DST_NAT_DONE | IPS_SRC_NAT_DONE),

	/* Connection is dying (removed from lists), can not be unset. */
	IPS_DYING_BIT = 9,
	IPS_DYING = (1 << IPS_DYING_BIT),

	/* Connection has fixed timeout. */
	IPS_FIXED_TIMEOUT_BIT = 10,
	IPS_FIXED_TIMEOUT = (1 << IPS_FIXED_TIMEOUT_BIT),

	/* Conntrack is a template */
	IPS_TEMPLATE_BIT = 11,
	IPS_TEMPLATE = (1 << IPS_TEMPLATE_BIT),

	/* Conntrack is a fake untracked entry.  Obsolete and not used anymore */
	IPS_UNTRACKED_BIT = 12,
	IPS_UNTRACKED = (1 << IPS_UNTRACKED_BIT),

	/* Conntrack got a helper explicitly attached via CT target. */
	IPS_HELPER_BIT = 13,
	IPS_HELPER = (1 << IPS_HELPER_BIT),

	/* Conntrack has been offloaded to flow table. */
	IPS_OFFLOAD_BIT = 14,
	IPS_OFFLOAD = (1 << IPS_OFFLOAD_BIT),

	/* Be careful here, modifying these bits can make things messy,
	 * so don't let users modify them directly.
	 */
	IPS_UNCHANGEABLE_MASK = (IPS_NAT_DONE_MASK | IPS_NAT_MASK |
				 IPS_EXPECTED | IPS_CONFIRMED | IPS_DYING |
				 IPS_SEQ_ADJUST | IPS_TEMPLATE | IPS_OFFLOAD),

	__IPS_MAX_BIT = 15,
};
```

## Example

* ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.dst.protonum
* ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.l3num;
* ct->tuplehash[dir].tuple.src.u3.ip;





## Call Graph


__ip_local_out


#### 接收数据


__netif_receive_skb_one_core -> __netif_receive_skb_core
__netif_receive_skb_one_core -> pt_prev->func:ipv6_rcv,ip_rcv
