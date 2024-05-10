#include <linux/module.h>
#include <linux/netfilter.h>

// static struct nf_hook_ops nf_inet_hooks[] __read_mostly = {
// 	{
// 		.pf = NFPROTO_INET,
// 		.hooknum = NF_INET_PRE_ROUTING,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = inet_pre_routing,
// 	},
// 	{
// 		.pf = NFPROTO_INET,
// 		.hooknum = NF_INET_LOCAL_IN,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = inet_local_in,
// 	},
// 	{
// 		.pf = NFPROTO_INET,
// 		.hooknum = NF_INET_FORWARD,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = inet_forward,
// 	},
// 	{
// 		.pf = NFPROTO_INET,
// 		.hooknum = NF_INET_LOCAL_OUT,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = inet_local_out,
// 	},
// 	{
// 		.pf = NFPROTO_INET,
// 		.hooknum = NF_INET_POST_ROUTING,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = inet_post_routing,
// 	}
// };


static unsigned int ipv4_pre_routing (void *priv,
	struct sk_buff *skb, const struct nf_hook_state *state)
{
	return NF_ACCEPT;
}

static unsigned int ipv4_local_in (void *priv,
	struct sk_buff *skb, const struct nf_hook_state *state)
{
	return NF_ACCEPT;
}

static unsigned int ipv4_forward (void *priv,
	struct sk_buff *skb, const struct nf_hook_state *state)
{
	return NF_ACCEPT;
}

static unsigned int ipv4_local_out (void *priv,
	struct sk_buff *skb, const struct nf_hook_state *state)
{
	return NF_ACCEPT;
}

static unsigned int ipv4_post_routing (void *priv,
	struct sk_buff *skb, const struct nf_hook_state *state)
{
	return NF_ACCEPT;
}

static struct nf_hook_ops nf_ipv4_hooks[] __read_mostly = {
	{
		.pf = NFPROTO_IPV4,
		.hooknum = NF_INET_PRE_ROUTING,
		.priority = NF_BR_PRI_FIRST,
		.hook = ipv4_pre_routing,
	},
	{
		.pf = NFPROTO_IPV4,
		.hooknum = NF_INET_LOCAL_IN,
		.priority = NF_BR_PRI_FIRST,
		.hook = ipv4_local_in,
	},
	{
		.pf = NFPROTO_IPV4,
		.hooknum = NF_INET_FORWARD,
		.priority = NF_BR_PRI_FIRST,
		.hook = ipv4_forward,
	},
	{
		.pf = NFPROTO_IPV4,
		.hooknum = NF_INET_LOCAL_OUT,
		.priority = NF_BR_PRI_FIRST,
		.hook = ipv4_local_out,
	},
	{
		.pf = NFPROTO_IPV4,
		.hooknum = NF_INET_POST_ROUTING,
		.priority = NF_BR_PRI_FIRST,
		.hook = ipv4_post_routing,
	}
};


static int __init nfhooks_init (void) {
	if ((ret = nf_register_hooks(nf_ipv4_hooks, ARRAY_SIZE(nf_ipv4_hooks))) < 0) {
		return ret;
	}

	return 0;
}

module_init(nfhooks_init);

static void __exit nfhooks_exit (void) {
	nf_unregister_hooks(nf_ipv4_hooks, ARRAY_SIZE(nf_ipv4_hooks));
}

module_exit(nfhooks_exit);

//


// static struct nf_hook_ops nf_bridge_hooks[] __read_mostly = {
// 	{
// 		.pf = NFPROTO_BRIDGE,
// 		.hooknum = NF_INET_PRE_ROUTING,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = bridge_pre_routing,
// 	}
// 	{
// 		.pf = NFPROTO_BRIDGE,
// 		.hooknum = NF_INET_LOCAL_IN,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = bridge_local_in,
// 	}
// 	{
// 		.pf = NFPROTO_BRIDGE,
// 		.hooknum = NF_INET_FORWARD,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = bridge_forward,
// 	}
// 	{
// 		.pf = NFPROTO_BRIDGE,
// 		.hooknum = NF_INET_LOCAL_OUT,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = bridge_local_out,
// 	}
// 	{
// 		.pf = NFPROTO_BRIDGE,
// 		.hooknum = NF_INET_POST_ROUTING,
// 		.priority = NF_BR_PRI_FIRST,
// 		.hook = bridge_post_routing,
// 	}
// };



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wenger Binning <wengerbinningh@gmail.com>");
MODULE_DESCRIPTION("test netfilter framework");