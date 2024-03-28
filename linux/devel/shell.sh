#!/bin/sh



file="crypto.txt"

while read line; do
    #
    test -n "$line" || continue
    #
    key=$(echo $line | cut -d':' -f1 | tr -d ' ')
    val=$(echo $line | cut -d':' -f2 | tr -d ' ')
    #
    case $key in
    name)
        name=$val; idx=$((idx + 1))
        prefix="crypto_alg_$idx"
        eval ${prefix}_name=\'$name\'
        name_len=$(echo $name | wc -c); name_len=$((name_len - 1))
        if [ ${name_len:-10} -gt ${name_max_len:-0} ]; then
            name_max_len=$name_len
        fi
        ;;
    driver)
        driver=$val
        eval ${prefix}_driver=\'$driver\'
        driver_len=$(echo $driver | wc -c); driver_len=$((driver_len - 1))
        if [ ${driver_len:-10} -gt ${driver_max_len:-0} ]; then
            driver_max_len=$driver_len
        fi
        ;;
    module)
        module=$val
        eval ${prefix}_module=\'$module\'
        module_len=$(echo $module | wc -c); module_len=$((module_len - 1))
        if [ ${module_len:-10} -gt ${module_max_len:-0} ]; then
            module_max_len=$module_len
        fi
        ;;
    priority)
        priority=$val
        eval ${prefix}_priority=\'$priority\'
        priority_len=$(echo $priority | wc -c); priority_len=$((priority_len - 1))
        if [ ${priority_len:-10} -gt ${priority_max_len:-0} ]; then
            priority_max_len=$priority_len
        fi
        ;;
    type)
        type=$val
        eval ${prefix}_type=\'$type\'
        type_len=$(echo $type | wc -c); type_len=$((type_len - 1))
        if [ ${type_len:-10} -gt ${type_max_len:-0} ]; then
            type_max_len=$type_len
        fi
        #
        CRYPTO_TYPE=${CRYPTO_TYPE:+$CRYPTO_TYPE }$type
        eval _table=\$${type}_table 
        _table="${_table:+$_table }$idx"
        eval ${type}_table=\'$_table\'
        ;;
    esac
done < $file

#
CRYPTO_TYPE=$(echo $CRYPTO_TYPE | tr -s ' ' '\n' | sort | uniq | xargs)

#echo $CRYPTO_TYPE
#echo $name_max_len $driver_max_len $type_max_len


for type in $CRYPTO_TYPE; do
    eval _table="\$${type}_table"
    echo "$type cipher"
    for idx in $_table; do
        prefix="crypto_alg_$idx"
        eval name=\$${prefix}_name
        eval driver=\$${prefix}_driver
        eval module=\$${prefix}_module
        eval priority=\$${prefix}_priority

        printf " - %02d name:%-${name_max_len}s module:%-${module_max_len}s driver:%-${driver_max_len}s priority:%${priority_max_len}d \n" $idx $name $module $driver $priority
    done
done