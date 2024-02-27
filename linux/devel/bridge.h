#ifndef __DEVEL_BRIDGE_H__
#define __DEVEL_BRIDGE_H__

struct net_bridge {
	spinlock_t			lock;
	spinlock_t			hash_lock;
	struct list_head		port_list;
	struct net_device		*dev;
	struct pcpu_sw_netstats		__percpu *stats;
	unsigned long			options;
	/* These fields are accessed on each packet */
#ifdef CONFIG_BRIDGE_VLAN_FILTERING
	__be16				vlan_proto;
	u16				default_pvid;
	struct net_bridge_vlan_group	__rcu *vlgrp;
#endif

	struct rhashtable		fdb_hash_tbl;
#if IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	union {
		struct rtable		fake_rtable;
		struct rt6_info		fake_rt6_info;
	};
#endif
	u16				group_fwd_mask;
	u16				group_fwd_mask_required;

	bool				disable_eap_hack;

	/* STP */
	bridge_id			designated_root;
	bridge_id			bridge_id;
	unsigned char			topology_change;
	unsigned char			topology_change_detected;
	u16				root_port;
	unsigned long			max_age;
	unsigned long			hello_time;
	unsigned long			forward_delay;
	unsigned long			ageing_time;
	unsigned long			bridge_max_age;
	unsigned long			bridge_hello_time;
	unsigned long			bridge_forward_delay;
	unsigned long			bridge_ageing_time;
	u32				root_path_cost;

	u8				group_addr[ETH_ALEN];

	enum {
		BR_NO_STP, 		/* no spanning tree */
		BR_KERNEL_STP,		/* old STP in kernel */
		BR_USER_STP,		/* new RSTP in userspace */
	} stp_enabled;

#ifdef CONFIG_BRIDGE_IGMP_SNOOPING

	u32				hash_max;

	u32				multicast_last_member_count;
	u32				multicast_startup_query_count;

	u8				multicast_igmp_version;
	u8				multicast_router;
#if IS_ENABLED(CONFIG_IPV6)
	u8				multicast_mld_version;
#endif
	spinlock_t			multicast_lock;
	unsigned long			multicast_last_member_interval;
	unsigned long			multicast_membership_interval;
	unsigned long			multicast_querier_interval;
	unsigned long			multicast_query_interval;
	unsigned long			multicast_query_response_interval;
	unsigned long			multicast_startup_query_interval;

	struct rhashtable		mdb_hash_tbl;

	struct hlist_head		mdb_list;
	struct hlist_head		router_list;

	struct timer_list		multicast_router_timer;
	struct bridge_mcast_other_query	ip4_other_query;
	struct bridge_mcast_own_query	ip4_own_query;
	struct bridge_mcast_querier	ip4_querier;
	struct bridge_mcast_stats	__percpu *mcast_stats;
#if IS_ENABLED(CONFIG_IPV6)
	struct bridge_mcast_other_query	ip6_other_query;
	struct bridge_mcast_own_query	ip6_own_query;
	struct bridge_mcast_querier	ip6_querier;
#endif /* IS_ENABLED(CONFIG_IPV6) */
#endif

	struct timer_list		hello_timer;
	struct timer_list		tcn_timer;
	struct timer_list		topology_change_timer;
	struct delayed_work		gc_work;
	struct kobject			*ifobj;
	u32				auto_cnt;

#ifdef CONFIG_NET_SWITCHDEV
	int offload_fwd_mark;
#endif
	struct hlist_head		fdb_list;
};


#endif /* __DEVEL_BRIDGE_H__ */