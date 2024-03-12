

#### struct net_device_ops

```c
struct net_device_ops {
	int	 (*ndo_init) (struct net_device *dev);
	void (*ndo_uninit) (struct net_device *dev);
	int  (*ndo_open) (struct net_device *dev);
	int	 (*ndo_stop) (struct net_device *dev);
	netdev_tx_t (*ndo_start_xmit) (struct sk_buff *skb, struct net_device *dev);
	netdev_features_t (*ndo_features_check) (struct sk_buff *skb, struct net_device *dev, netdev_features_t features);
	u16	 (*ndo_select_queue) (struct net_device *dev, struct sk_buff *skb, struct net_device *sb_dev);
	void (*ndo_change_rx_flags) (struct net_device *dev, int flags);
	void (*ndo_set_rx_mode) (struct net_device *dev);
	int	 (*ndo_set_mac_address) (struct net_device *dev, void *addr);
	int	 (*ndo_validate_addr) (struct net_device *dev);
	int	 (*ndo_do_ioctl) (struct net_device *dev, struct ifreq *ifr, int cmd);
	int	 (*ndo_set_config) (struct net_device *dev, struct ifmap *map);
	int	 (*ndo_change_mtu) (struct net_device *dev, int new_mtu);
	int	 (*ndo_neigh_setup) (struct net_device *dev, struct neigh_parms *);
	void (*ndo_tx_timeout) (struct net_device *dev);
	void (*ndo_get_stats64) (struct net_device *dev, struct rtnl_link_stats64 *storage);
	bool (*ndo_has_offload_stats) (const struct net_device *dev, int attr_id);
	int	 (*ndo_get_offload_stats) (int attr_id, const struct net_device *dev, void *attr_data);
	struct net_device_stats* (*ndo_get_stats) (struct net_device *dev);
	int	 (*ndo_vlan_rx_add_vid) (struct net_device *dev, __be16 proto, u16 vid);
	int	 (*ndo_vlan_rx_kill_vid) (struct net_device *dev, __be16 proto, u16 vid);

#ifdef CONFIG_NET_POLL_CONTROLLER
	void (*ndo_poll_controller) (struct net_device *dev);
	int  (*ndo_netpoll_setup) (struct net_device *dev, struct netpoll_info *info);
	void (*ndo_netpoll_cleanup) (struct net_device *dev);
#endif

	int (*ndo_set_vf_mac)(struct net_device *dev, int queue, u8 *mac);
	int	(*ndo_set_vf_vlan)(struct net_device *dev, int queue, u16 vlan, u8 qos, __be16 proto);
	int	(*ndo_set_vf_rate)(struct net_device *dev, int vf, int min_tx_rate, int max_tx_rate);
	int	(*ndo_set_vf_spoofchk)(struct net_device *dev, int vf, bool setting);
	int	(*ndo_set_vf_trust)(struct net_device *dev, int vf, bool setting);
	int	(*ndo_get_vf_config)(struct net_device *dev, int vf, struct ifla_vf_info *ivf);
	int	(*ndo_set_vf_link_state)(struct net_device *dev, int vf, int link_state);
	int	(*ndo_get_vf_stats)(struct net_device *dev, int vf, struct ifla_vf_stats *vf_stats);
	int	(*ndo_set_vf_port)(struct net_device *dev, int vf, struct nlattr *port[]);
	int	(*ndo_get_vf_port)(struct net_device *dev, int vf, struct sk_buff *skb);
	int	(*ndo_set_vf_guid)(struct net_device *dev, int vf, u64 guid, int guid_type);
	int	(*ndo_set_vf_rss_query_en) (struct net_device *dev, int vf, bool setting);
	int	(*ndo_setup_tc)(struct net_device *dev, enum tc_setup_type type, void *type_data);

#if IS_ENABLED(CONFIG_FCOE)
	int (*ndo_fcoe_enable)(struct net_device *dev);
	int	(*ndo_fcoe_disable)(struct net_device *dev);
	int	(*ndo_fcoe_ddp_setup)(struct net_device *dev, u16 xid, struct scatterlist *sgl, unsigned int sgc);
	int	(*ndo_fcoe_ddp_done)(struct net_device *dev, u16 xid);
	int	(*ndo_fcoe_ddp_target)(struct net_device *dev, u16 xid, struct scatterlist *sgl, unsigned int sgc);
	int	(*ndo_fcoe_get_hbainfo)(struct net_device *dev, struct netdev_fcoe_hbainfo *hbainfo);
#endif

#if IS_ENABLED(CONFIG_LIBFCOE)
#define NETDEV_FCOE_WWNN 0
#define NETDEV_FCOE_WWPN 1
	int (*ndo_fcoe_get_wwn)(struct net_device *dev, u64 *wwn, int type);
#endif

#ifdef CONFIG_RFS_ACCEL
	int (*ndo_rx_flow_steer) (struct net_device *dev, const struct sk_buff *skb, u16 rxq_index, u32 flow_id);
#endif

	int  (*ndo_add_slave) (struct net_device *dev, struct net_device *slave_dev, struct netlink_ext_ack *extack);
	int  (*ndo_del_slave) (struct net_device *dev, struct net_device *slave_dev);
	netdev_features_t (*ndo_fix_features)(struct net_device *dev, netdev_features_t features);
	int  (*ndo_set_features)(struct net_device *dev, netdev_features_t features);
	int  (*ndo_neigh_construct) (struct net_device *dev, struct neighbour *n);
	void (*ndo_neigh_destroy) (struct net_device *dev, struct neighbour *n);

	int (*ndo_fdb_add) (struct ndmsg *ndm, struct nlattr *tb[], struct net_device *dev, const unsigned char *addr, u16 vid, u16 flags, struct netlink_ext_ack *extack);
	int	(*ndo_fdb_del) (struct ndmsg *ndm, struct nlattr *tb[], struct net_device *dev, const unsigned char *addr, u16 vid);
	int (*ndo_fdb_dump) (struct sk_buff *skb, struct netlink_callback *cb, struct net_device *dev, struct net_device *filter_dev, int *idx);
	int (*ndo_fdb_get) (struct sk_buff *skb, struct nlattr *tb[], struct net_device *dev, const unsigned char *addr, u16 vid, u32 portid, u32 seq, struct netlink_ext_ack *extack);
	int	(*ndo_bridge_setlink) (struct net_device *dev, struct nlmsghdr *nlh, u16 flags, struct netlink_ext_ack *extack);
	int	(*ndo_bridge_getlink) (struct sk_buff *skb, u32 pid, u32 seq, struct net_device *dev, u32 filter_mask, int nlflags);
	int (*ndo_bridge_dellink) (struct net_device *dev, struct nlmsghdr *nlh, u16 flags);
	
	int (*ndo_flow_offload_check) (struct flow_offload_hw_path *path);
	int	(*ndo_flow_offload) (enum flow_offload_type type, struct flow_offload *flow, struct flow_offload_hw_path *src, struct flow_offload_hw_path *dest);

	int	  (*ndo_change_carrier) (struct net_device *dev, bool new_carrier);
	int	  (*ndo_get_phys_port_id) (struct net_device *dev, struct netdev_phys_item_id *ppid);
	int	  (*ndo_get_port_parent_id) (struct net_device *dev, struct netdev_phys_item_id *ppid);
	int	  (*ndo_get_phys_port_name) (struct net_device *dev, char *name, size_t len);
	void  (*ndo_udp_tunnel_add) (struct net_device *dev, struct udp_tunnel_info *ti);
	void  (*ndo_udp_tunnel_del) (struct net_device *dev, struct udp_tunnel_info *ti);
	void* (*ndo_dfwd_add_station) (struct net_device *pdev, struct net_device *dev);
	void  (*ndo_dfwd_del_station) (struct net_device *pdev, void *priv);
	int	  (*ndo_set_tx_maxrate) (struct net_device *dev, int queue_index, u32 maxrate);
	int	  (*ndo_get_iflink) (const struct net_device *dev);
	int	  (*ndo_change_proto_down) (struct net_device *dev, bool proto_down);
	int	  (*ndo_fill_metadata_dst) (struct net_device *dev, struct sk_buff *skb);
	void  (*ndo_set_rx_headroom) (struct net_device *dev, int needed_headroom);
	int	  (*ndo_bpf) (struct net_device *dev, struct netdev_bpf *bpf);
	int	  (*ndo_xdp_xmit) (struct net_device *dev, int n, struct xdp_frame **xdp, u32 flags);
	int	  (*ndo_xsk_wakeup) (struct net_device *dev, u32 queue_id, u32 flags);
	
	struct devlink_port *(*ndo_get_devlink_port) (struct net_device *dev);
};
```