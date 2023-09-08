#!/usr/bin/env sh



running=true






demo_exit() {
    echo -e "\nEXIT SCRIPT"
}

trap "demo_exit" EXIT
idx=0

while [ $running==true ]; do
    echo "runnning $idx time ..."
    idx=$((idx + 1))
    sleep 1
done