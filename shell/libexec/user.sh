#!/bin/sh 

# command depends:
# whoami id


# usage: user_root_privilege
user_root_privilege() {
    local cur_usr=$(whoami)
    local cur_uid=$(id -u $cur_usr)
    if [ $cur_uid != 0 ]; then
        echo "Please execute with sudo or switch to root privileges" >&2
        return 1
    fi
}