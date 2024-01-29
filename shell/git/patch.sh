targetdir=${1}; targetdir=$(cd $targetdir && pwd)
patchdir=${2:-patch}; patchdir=$(cd $patchdir && pwd)





test -d "$targetdir" || {
	echo "$0 <target repo> <patch directory>"
	exit 0
}

# ============================================================================ #

error() {
	echo -ne '\e[31m'
	echo -ne "$@"
	echo -ne '\e[0m'
	echo -ne '\n'
}

warning() {
	echo -ne '\e[33m'
	echo -ne "$@"
	echo -ne '\e[0m'
	echo -ne '\n'
}

notice() {
	echo -ne '\e[34m'
	echo -ne "$@"
	echo -ne '\e[0m'
	echo -ne '\n'
}

info() {
	echo -ne '\e[32m'
	echo -ne "$@"
	echo -ne '\e[0m'
	echo -ne '\n'
}

debug() {
	echo -ne '\e[92m'
	echo -ne "$@"
	echo -ne '\e[0m'
	echo -ne '\n'
}

# ---------------------------------------------------------------------------- #

git_patch_check() {
	local patch=$1
	echo -e "\e[34mChecking patch ...\e[0m"
	#
	result=$(sed -nre '1 p' $patch)
	prefix=$(echo $result | cut -d' ' -f1)
	test "$prefix" == "From" || return 1
	commit_id=$(echo $result | cut -d' ' -f2)
	# #
	# result=$(sed -nre '2 p' $patch)
	# prefix=$(echo $result | cut -d' ' -f1)
	# test "$prefix" == "From:" || return 1
	# commit_author=$(echo $result | cut -d' ' -f2-)
	# #
	# result=$(sed -nre '3 p' $patch)
	# prefix=$(echo $result | cut -d' ' -f1)
	# test "$prefix" == "Date:" || return 1
	# commit_date=$(echo $result | cut -d' ' -f2-)
	# #
	# result=$(sed -nre '4 p' $patch)
	# prefix=$(echo $result | cut -d' ' -f1)
	# test "$prefix" == "Subject:" || return 1
	# commit_subject=$(echo $result | cut -d' ' -f2-)
}
#
patch_apply() {
	# patch -p1 -f < $patch
	local patch=$1
	local result line
	#
	result=$(grep -n $patch .patch_passed 2>/dev/null) && {
		line=$(echo $result | cut -d':' -f1)
		warning "This patch has been imported!"
		return 0
	}
	#
	result=$(grep -n $patch .patch_skiped 2>/dev/null) && {
		line=$(echo $result | cut -d':' -f1)
		warning "This patch found in .patch_skiped(line $line), so needs to be skipped!"
		sed -i "$line d" .patch_failed
		echo $patch >> .patch_passed
		return 0
	}
	#
	git apply --check $patch; ret=$?
	git_patch_check $patch && {
		#
		debug "Apply patch ..."
		git am $patch; ret=$?
		case $ret in
		0);;
		*) git am --abort
		esac
	} || {
		#
		debug "Patch file ..."
		git apply $patch; ret=$?
		case $ret in
		0)
			result=$(basename $patch); result=${result%.patch}
			prefix=$(echo $result | cut -d'-' -f1)
			_idx=0
			while [[ "$prefix" =~ '^[0-9]' ]]; do _idx=$((_idx + 1))
				test $_idx -gt 5 && warning "Here has a bug !!!!!!"
				result=$(echo $result | cut -d'-' -f2-)
				prefix=$(echo $result | cut -d'-' -f1)
			done
			default_message=$(date +%Y-%m-%d-%H%M%S%z)
			message=${result:-$default_message}
			debug "Commit change ..."
			git add . || return 1
			git commit -m "${message}"; ret=$?
		;;
		*)
			error "Patch file failed!"
		esac
	}
	case $ret in
	0) echo $patch >> .patch_passed;;
	*)
		result=$(grep -n $patch .patch_failed 2>/dev/null) || {
			echo $patch >> .patch_failed
		}
	esac
	return $ret
}

# ============================================================================ #

cd $targetdir
result=passed
#old_idx=$(cat .patch_idx 2>/dev/null);
idx=${old_idx:-0}
total=$(ls -1 $patchdir/*.patch |wc -l)
count=0
for file in $(ls "$patchdir"); do idx=$((idx + 1))
	case ${file##*.} in
	patch)
		git checkout .
		git clean -fd .
		info "Start apply $idx/$total patch: $patchdir/$file ..."
		patch_apply "$patchdir/$file" && {
			#
			count=$((count + 1))
		} || {
			#
			read -p "Skip this patch file(Y/n):" cmd
			case ${cmd} in
			N|n|no)
				;;
			*)
				continue
			esac
			#
			exit
		}
	esac
done

if [ $count -eq $total ]; then
	notice "From $patchdir apply patch to $targetdir Successful!"
fi

cd - >/dev/null
