
* xt_FLOWOFFLOAD.c

## symbols

#### linux

* linux/module.h
* linux/init.h
* linux/netfilter.h

* linux/netfilter/xt_FLOWOFFLOAD.h

* net/ip.h


* net/netfilter/nf_conntrack.h
* net/netfilter/nf_conntrack_extend.h
* net/netfilter/nf_conntrack_helper.h
* net/netfilter/nf_flow_table.h


### static

* nf_flowtable

* hooks
* hooks_lock

* hook_work

* struct xt_flowoffload_hook


* nf_flow_table_iterate
* flow_offload_lookup_hook

* xt_flowoffload_net_hook
* xt_flowoffload_create_hook
* xt_flowoffload_check_device

* xt_flowoffload_register_hooks
* xt_flowoffload_cleanup_hooks

* xt_flowoffload_check_hook

* xt_flowoffload_hook_work

* xt_flowoffload_skip
* xt_flowoffload_dst
* xt_flowoffload_route

* offload_tg_reg

* flowoffload_tg
* flowoffload_chk

* xt_flowoffload_table_init
* xt_flowoffload_table_cleanup

* flow_offload_netdev_notifier
* flow_offload_netdev_event

* xt_flowoffload_tg_init
* xt_flowoffload_tg_exit





## callgraph

flowoffload_tg -> xt_flowoffload_route
flowoffload_tg -> flow_offload_add
flowoffload_tg -> nf_flow_offload_hw_add

flow_offload_netdev_event -> flow_offload_lookup_hook


xt_flowoffload_hook_work -> xt_flowoffload_register_hooks
xt_flowoffload_hook_work -> xt_flowoffload_check_hook
xt_flowoffload_hook_work -> xt_flowoffload_cleanup_hooks