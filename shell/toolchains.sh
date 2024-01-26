
environment=$1;
test -f $environment || { exit 1; }
environment_name=$(basename $environment)
environment_home=$(cd $(dirname $environment) && pwd)
environment=$environment_home/$environment_name

#echo $environment

TOOLCHAIN=$(basename $environment_home)
TOOLCHAINS=$(dirname $environment_home)

#echo $TOOLCHAINS
#echo $TOOLCHAIN


variable_override() {

}

variable_default() {

}

variable_insert

while read line; do
	line=$(echo $line | tr -s ' ')
	prefix=$(echo $line | cut -c 1)
	case $prefix in
	'#')
		continue;;
	esac
	#
	#echo "$line"
	#
	key=$(echo "$line" | cut -d' ' -f1)
	case $key in
	export)
		table=$(echo "$line" | cut -d' ' -f2-)
		echo "export $table"
		continue;;
	esac
	#
	var=$(echo "$line" | sed -nre 's/^(.*)(.=)(.*)$/\1/p')
	opt=$(echo "$line" | sed -nre 's/^(.*)(.=)(.*)$/\2/p')
	val=$(echo "$line" | sed -nre 's/^(.*)(.=)(.*)$/\3/p')
	#echo $var
	#echo $opt
	#echo $val
	#
	case $opt in
	=|:=)
		echo "Overide $var"
		;;
	?=)
		echo "fallback $var"
		;;
	+=)
		echo "Append $var"
		;;
	esac
	#
done < $environment

