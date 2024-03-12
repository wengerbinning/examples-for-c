


ip_forward -> xfrm4_policy_check
ip_forward -> xfrm4_route_forward
ip_forward -> NF_HOOK(NF_INET_FORWARD) -> ip_forward_finish

