
dir_scan() {
	local cwd=${1:-PWD} dir dirs table
	cd $cwd && {
		dirs=$(find ./ -mindepth 1 -maxdepth 1 -type d)
		for dir in ${dirs}; do dir=${dir#./}
			test -d $dir || continue
			#
			table="${table:+$table }$dir"
		done
		cd - >/dev/null
	}
	echo "$table"
}

app_check() {
	local app=$1

	#
	test -d $app/rootfs || {
		test -f $app/rootfs.tar.gz || return 1
	}
	#
	test -f $app/files.info || return 1

}

# usage: _app_scan <idx> <path>
_app_scan() {
	local idx=$1; shift
	local dir apps dirs
	for dir in $@; do dir=${dir%/}
		app_check $dir && {
			apps=${apps:+$apps }$dir
		} || {
			_dirs=$(dir_scan $dir)
			for _dir in $_dirs; do
				dirs=${dirs:+$dirs }$dir/$_dir
			done
		}
	done
	test -n "$apps" && echo "apps:$apps"
	test -n "$dirs" && echo "dirs:$dirs"
}

app_scan() {
	local dirs=$@ i
	for i in $(seq 1 1 ${SCAN_DEPTH:-4}); do
		result=$(_app_scan $i $dirs)
		apps=$(echo "$result" | sed -nre 's/^apps:(.*)/\1/p')
		dirs=$(echo "$result" | sed -nre 's/^dirs:(.*)/\1/p')
		test -n "$apps" && APPS=${APPS:+$APPS }$apps
		test -n "$dirs" || break
	done
}

##
# usage: app_install <src> <dst> [policy]
app_install() {
	local src_rootfs=${1:-$SRC_ROOTFS}; src_rootfs=${src_rootfs:-$PWD/rootfs}
	local dst_rootfs=${2:-$DST_ROOTFS}; dst_rootfs=${dst_rootfs:-$PWD/dst_rootfs}
	local policy=${3:-POLICY}; policy=${policy:-embed}
	local file
	#
	case $policy in
	embed) file="embed-files.installed" ;;
	*)     file="files.installed"
	esac
	#
	while read line; do
		#
		test -n "$line" || continue
		#
		prefix=$(echo $line | cut -c 1)
		case $prefix in
		'#') continue;;
		esac
		#
		_type=file; _mode=664
		suffix=${line:0-1:1}; line=${line%[*/=@>]}
		case $suffix in
		'*') type=file; mode=775 ;;
		'/') type=dire; mode=755 ;;
		esac
		#
		case $_type in
		file)
			_path=${line%/*}; _file=${line##*/}
			install -m 775 -d ${dst_rootfs}/$_path
			install -m $_mode -t ${dst_rootfs}/$_path ${src_rootfs}/$_path/$_file
		;;
		dire)
			_path=${line}
			install -m 775 -d ${dst_rootfs}/$_path
		;;
		*) echo $line
		esac
	done < $file
}









app_scan ./

for app in $APPS; do
	echo $app
done