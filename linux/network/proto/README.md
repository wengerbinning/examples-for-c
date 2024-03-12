

ip_rcv -> NF_HOOK(NF_INET_PRE_ROUTING) -> ip_rcv_finish
ip_sublist_rcv -> NF_HOOK_LIST(NF_INET_PRE_ROUTING) -> ip_rcv_finish
ip_sublist_rcv -> ip_list_rcv_finish

ip_rcv_finish -> ip_rcv_finish_core
ip_rcv_finish -> dst_input

ip_list_rcv_finish -> ip_rcv_finish_core

ip_rcv_finish_core -> ip_route_input_noref






ip_local_deliver -> ip_local_deliver_finish




__ip_local_out -> nf_hook(NFPROTO_IPV4,NF_INET_LOCAL_OUT,dst_output)