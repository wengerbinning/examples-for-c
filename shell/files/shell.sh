




ipsec_client_get_tunnel_info "client0"






sys_idle_rate() {
    result=$(cat /proc/uptime)
    up_time=$(echo $time | cut -d' ' -f1)
    idle_time=$(echo $time | cut -d' ' -f2)
    ncpus=$(cat /proc/cpuinfo | grep processor | wc -l)

    ((idle_time / up_time * ncpus))
}