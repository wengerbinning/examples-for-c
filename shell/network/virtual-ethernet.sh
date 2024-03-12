
DEFAULT_VIRTUAL_BRIDGE="vbridge0"
DEFAULT_IPV4_STATIC_ADDRESS="192.168.10.1/24"

DEFAULT_VIRTUAL_ETHERNET="veth0"

SCRIPT_ACTION_SHOW=true
SCRIPT_METHOD="dummy"


# usage: show_virtual_ethernet_create <ethernet name>
show_virtual_ethernet_create() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
    #
    echo "ip link add $veth type dummy"
    #
    echo "ip link set dev $veth up"

}

# usage: virtual_ethernet_create <ethernet name>
virtual_ethernet_create() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
    #
    test -n "$SCRIPT_ACTION_SHOW" && {
        show_virtual_ethernet_create $@
        return $?
    }
    #
    ip link add $veth type dummy
    #
    ip link set dev $veth up
}

# usage: show_virtual_ethernet_add_to_bridge <ethernet name> <bridge name>
show_virtual_ethernet_add_to_bridge() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
    local br=${2:-$DEFAULT_VIRTUAL_BRIDGE}
    #
    echo "ip link set $veth master $br"

}

# usage: virtual_ethernet_add_to_bridge <ethernet name> <bridge name>
virtual_ethernet_add_to_bridge() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
    local br=${2:-$DEFAULT_VIRTUAL_BRIDGE}
    #
    test -n "$SCRIPT_ACTION_SHOW" && {
        show_virtual_ethernet_add_to_bridge $@
        return $?
    }
    #
    ip link set $veth master $br
}


case $SCRIPT_METHOD in
"dummy")
    virtual_ethernet_create
    virtual_ethernet_add_to_bridge
;;
esac



# <https://linuxconfig.org/configuring-virtual-network-interfaces-in-linux>