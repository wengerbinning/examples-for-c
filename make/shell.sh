a=1



b() {
    a=${a:+$a }$(echo 123 | tr -d '2')
}


b

echo $a


git_check() {
	local repo=$1 ret
	test -d $repo || return 1
	cd $repo || return 1
    ret=$(git rev-parse --is-bare-repository 2>/dev/null)
    cd - >/dev/null
	case $ret in
	true)	return 0;;
	*)		return 1;;
	esac
}

dir_check() {
    local cwd=${1:-./}; cwd=${cwd%/}
    local dir dirs git repos table
    dirs=$(scan_dir $cwd)
    for dir in $dirs; do
        echo "start $cwd/$dir ..."
        git_check $cwd/$dir; ret=$?
        echo $ret
        case $ret in
        0) repos=${repos:+$repos }$cwd/$dir;;
        *) table=${table:+$table }$cwd/$dir;;
        esac
    done
    echo "git:$repos"
    echo "dir:$table"
}
