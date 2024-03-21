include/uapi/linux/net_namespace.h
include/net/net_namespace.h

include/uapi/linux/netdevice.h
include/linux/netdevice.h

net/core/**



for_each_netdev_rcu



for_each_net


Author: Wenbin Zheng <wbzheng@grandstream.cn>
Date:   Tue Mar 19 15:32:51 2024 +0800

[NBF] Optimizing get default lan device in GCC6011.

Cause: We need to differentiate the default LAN device at runtime
Solution: We obtain the device names in order according to the priority of device existence.
Fixed Version: None
Branch: router_master