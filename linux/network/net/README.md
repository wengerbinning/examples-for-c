
* struct dst_entry



## Call Graph

dst_output -> dst->output:


dst->output:
    xfrm4_output
    






#### 接收数据


inet_recvmsg -> sk->sk_prot->recvmsg:udp_recvmsg
