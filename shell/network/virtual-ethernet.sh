


DEFAULT_IPV4_STATIC_ADDRESS="192.168.10.1/24"

SCRIPT_METHOD="tap"

DEFAULT_VIRTUAL_DUMMY="veth0"
DEFAULT_VIRTUAL_TAP="vtap0"
DEFAULT_VIRTUAL_TUN="vtun0"
DEFAULT_VIRTUAL_BRIDGE="vbridge0"

case $SCRIPT_METHOD in
dummy)   DEFAULT_VIRTUAL_ETHERNET=$DEFAULT_VIRTUAL_DUMMY  ;;
tap)     DEFAULT_VIRTUAL_ETHERNET=$DEFAULT_VIRTUAL_TAP    ;;
tun)     DEFAULT_VIRTUAL_ETHERNET=$DEFAULT_VIRTUAL_TUN    ;;
bridge)  DEFAULT_VIRTUAL_ETHERNET=$DEFAULT_VIRTUAL_BRIDGE ;;
*)       DEFAULT_VIRTUAL_ETHERNET=$DEFAULT_VIRTUAL_DUMMY
esac

CMD_ROOT=true

# usage: runcmd <command>
runcmd() {
	local cmd opts=$@
	test $# -gt 0 || return
	if ${CMD_SHOW:-true}; then cmd=echo; else cmd=eval; fi
	if ${CMD_ROOT:-false}; then opt=sudo; else opt='';   fi
	${cmd} " ${opt:+$opt }$@"
}

cmdset() {
	if ${CMD_SHOW:-true}; then echo "# $@"; fi

}

# usage: virtual_ethernet_veth_create <ethernet name>
virtual_ethernet_veth_create() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
	#
	cmdset Create Veth virtual Ethernet
    #
    runcmd ip link add $veth type veth
    #
    runcmd ip link set dev $veth up
}

# usage: virtual_ethernet_dummy_create <ethernet name>
virtual_ethernet_dummy_create() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
	#
	cmdset Create Dummy virtual Ethernet
    #
    runcmd ip link add $veth type dummy
    #
    runcmd ip link set dev $veth up
}

# usage: virtual_ethernet_tap_create <ethernet name>
virtual_ethernet_tap_create() {
	local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
	#
	cmdset Create Tap Virtual Ethernet
	#
	runcmd ip tuntap add $veth mode tap
	#
	runcmd ip link set $veth up
}

# usage: virtual_ethernet_tun_create <ethernet name>
virtual_ethernet_tun_create() {
	local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
	#
	cmdset Create Tun Virtual Ethernet
	#
	runcmd ip tuntap add $veth mode tun
	#
	runcmd ip link set $veth up
}

# usage: virtual_ethernet_bridge_create <ethernet name>
virtual_ethernet_bridge_create() {
	local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
	#
	cmdset Create Birdge Virtual Ethernet
	#
	runcmd ip link add $veth mode bridge
	#
	runcmd ip link set $veth up
}



# usage: virtual_ethernet_add_to_bridge <ethernet name> <bridge name>
virtual_ethernet_add_to_bridge() {
    local veth=${1:-$DEFAULT_VIRTUAL_ETHERNET}
    local br=${2:-$DEFAULT_VIRTUAL_BRIDGE}
	#
	cmdset Add device to bridge
    #
    runcmd ip link set $veth master $br
}

case $SCRIPT_METHOD in
"dummy")
	virtual_ethernet_dummy_create
	#virtual_ethernet_add_to_bridge
;;
"tap")
	virtual_ethernet_tap_create
	virtual_ethernet_add_to_bridge
;;
"tun")
	virtual_ethernet_tun_create
	virtual_ethernet_add_to_bridge
;;
"bridge")
	virtual_ethernet_bridge_create
;;
esac



# <https://linuxconfig.org/configuring-virtual-network-interfaces-in-linux>