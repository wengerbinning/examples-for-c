


#### 发送数据

ip_send_skb -> ip_local_out
ip_send_skb -> net_xmit_errno

ip_local_out -> __ip_local_out
ip_local_out -> dst_output

__ip_local_out -> ip_hdr
__ip_local_out -> ip_send_check
__ip_local_out -> l3mdev_ip_out
__ip_local_out -> nf_hook(NFPROTO_IPV4,NF_INET_LOCAL_OUT,dst_output)



#### 接收数据


ip_rcv -> ip_rcv_core
ip_rcv -> NF_HOOK(NFPROTO_IPV4,NF_INET_PRE_ROUTING,ip_rcv_finish)

ip_rcv_finish -> l3mdev_ip_rcv
ip_rcv_finish -> ip_rcv_finish_core
ip_rcv_finish -> dst_input:
    ip_local_deliver
    ip_forward

ip_local_deliver -> NF_HOOK(NFPROTO_IPV4,NF_INET_LOCAL_IN,ip_local_deliver_finish)

ip_local_deliver_finish -> __skb_pull
ip_local_deliver_finish -> ip_protocol_deliver_rcu

ip_protocol_deliver_rcu -> raw_local_deliver
ip_protocol_deliver_rcu -> xfrm4_policy_check(XFRM_POLICY_IN,skb)
ip_protocol_deliver_rcu -> nf_reset_ct
ip_protocol_deliver_rcu -> ipprot->handler:tcp_v4_rcv,udp_rcv,tunnel4_rcv
ip_protocol_deliver_rcu -> xfrm4_policy_check(XFRM_POLICY_IN,skb)

raw_local_deliver -> raw_v4_input

raw_v4_input -> __raw_v4_lookup
raw_v4_input -> raw_rcv