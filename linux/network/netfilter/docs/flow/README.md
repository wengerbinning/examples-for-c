



* nf_flow_table_core.c
* nf_flow_table_hw.c

### static

* struct flow_offload_entry

* flowtable_lock
* flowtables


* flow_offload_dst_cookie
* flow_offload_fill_dir
* flow_offload_fixup_tcp
* nf_flow_timeout_delta
* flow_offload_fixup_ct_timeout
* flow_offload_fixup_ct_state
* flow_offload_fixup_ct

* flow_offload_hash
* flow_offload_hash_obj
* flow_offload_hash_cmp


* flow_offload_hw_pending_list - struct list_head
* flow_offload_hw_pending_list_lock
* struct flow_offload_hw



* nf_flow_offload_rhash_params

* nf_ct_offload_timeout


### public

* flow_offload_alloc
* flow_offload_free
* nf_flow_table_acct

* flow_offload_add


* nf_flow_table_hw_register
* nf_flow_table_hw_unregister

* nf_flow_offload_hw_work - struct work_struct
* do_flow_offload_hw
* flow_offload_hw_work


* flow_offload_hw_prepare
* flow_offload_check_path

* flow_offload_hw - struct nf_flow_table_hw
* flow_offload_hw_add
* flow_offload_hw_del

* nf_flow_table_hw_module_init
* nf_flow_table_hw_module_exit

## callgraph

nf_flow_offload_hw_add -> nf_flow_table_hw_hook->add

flow_offload_hw_add -> flow_offload_hw_prepare
flow_offload_hw_add -> flow_offload_queue_work
flow_offload_hw_del -> flow_offload_hw_prepare
flow_offload_hw_del -> flow_offload_queue_work

flow_offload_hw_prepare -> flow_offload_check_path
flow_offload_check_path -> dev->netdev_ops->ndo_flow_offload_check


flow_offload_hw_work -> do_flow_offload_hw

do_flow_offload_hw -> src_dev->netdev_ops->ndo_flow_offload