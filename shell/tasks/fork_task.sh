



# usage: start_task <pid file> <command>...
start_task() {
    local shell="/bin/sh"
    local task=$1; shift
    local cmd="$@"
    test -f "$task" kill $(cat $task)
    eval "$shell -c 'echo \$\$ > $task; exec time $cmd' &"
}



finsih_task() {
    local task=$1; shift
    test -f "$task" kill $(cat $task)
}


