


#### Export Symbol Table

* sock_alloc_file
* sock_from_file
* sockfd_lookup

* sock_alloc

* sock_sendmsg
* kernel_sendmsg
* kernel_sendmsg_locked

* sock_recvmsg
* kernel_recvmsg



## Call Graph


#### 发送数据

sock_sendmsg -> security_socket_sendmsg
sock_sendmsg -> sock_sendmsg_nosec -> sock->ops->sendmsg:inet6_sendmsg,inet_sendmsg

inet_sendmsg -> inet_send_prepare
inet_sendmsg -> sk->sk_prot->sendmsg:tcp_sendmsg,udp_sendmsg


#### 接收数据

sock_recvmsg -> sock_recvmsg_nosec -> inet_recvmsg -> sock->ops->recvmsg:inet6_recvmsg,inet_recvmsg
