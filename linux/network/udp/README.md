



#### 发送数据

udp_sendmsg -> ipcm_init_sk
udp_sendmsg -> udp_cmsg_send
udp_sendmsg -> ip_cmsg_send
udp_sendmsg -> inet_sk_flowi_flags
udp_sendmsg -> flowi4_init_output
udp_sendmsg -> security_sk_classify_flow
udp_sendmsg -> ip_route_output_flow
udp_sendmsg -> ip_make_skb
udp_sendmsg -> udp_send_skb

udp_send_skb -> skb_transport_offset
udp_send_skb -> udp_hdr
udp_send_skb -> csum_tcpudp_magic
udp_send_skb -> ip_send_skb

#### 接收数据

udp_recvmsg -> __skb_recv_udp
udp_recvmsg -> copy_linear_skb
udp_recvmsg -> skb_copy_datagram_msg
udp_recvmsg -> skb_copy_and_csum_datagram_msg
udp_recvmsg -> skb_consume_udp

skb_consume_udp