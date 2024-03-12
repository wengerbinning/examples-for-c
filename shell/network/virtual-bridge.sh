
DEFAULT_VIRTUAL_BRIDGE="vbridge0"
DEFAULT_IPV4_STATIC_ADDRESS="192.168.10.1/24"

SCRIPT_ACTION_SHOW=true


# usage: show_virtual_bridge_create <bridge name>
show_virtual_bridge_create() {
    local vbr=${1:-$DEFAULT_VIRTUAL_BRIDGE}
    #
    echo "ip link add $vbr type bridge"
    #
    echo "ip link set dev $vbr up"
}

# usage: virtual_bridge_create <bridge name>
virtual_bridge_create() {
    local vbr=${1:-$DEFAULT_VIRTUAL_BRIDGE}
    #
    test -n "$SCRIPT_ACTION_SHOW" && {
        show_virtual_bridge_create $@
        return $?
    }
    #
    ip link add $vbr type bridge
    #
    ip link set dev $vbr up
}

# usage: show_virtual_bridge_set_static_addr <bridge name> <ip address with submask>
show_virtual_bridge_set_static_addr() {
    local vbr=${1:-$DEFAULT_VIRTUAL_BRIDGE}
    local vbr_ip=${2:-$DEFAULT_IPV4_STATIC_ADDRESS}
    #
    echo "ip addr add $vbr_ip dev $vbr"
}

# usage: virtual_bridge_set_static_addr <bridge name> <ip address with submask>
virtual_bridge_set_static_addr() {
    local vbr=${1:-$DEFAULT_VIRTUAL_BRIDGE}
    local vbr_ip=${2:-$DEFAULT_IPV4_STATIC_ADDRESS}
    #
    test -n "$SCRIPT_ACTION_SHOW" && {
        show_virtual_bridge_set_static_addr $@
        return $?
    }
    #
    ip addr add $vbr_ip dev $vbr
}




virtual_bridge_create
virtual_bridge_set_static_addr




# <https://developers.redhat.com/blog/2018/10/22/introduction-to-linux-interfaces-for-virtual-networking#bridge>