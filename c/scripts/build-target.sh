#!/usr/bin/env bash

MOD_MAX_PATH=4

# usage: mod_target <mod> <target>...
mod_target() {
	local mod dep target val _val var each
	local mods relos execs stlibs shlibs
	mod=$1; dep=$2; shift 2
	[ ${dep:-0} -lt ${MOD_MAX_PATH:-4} ] || return
	test -f "${mod}/.target" && target=$(cat ${mod}/.target)
	[ -n "$target" ] || return
	mods=$(echo "$target" | sed -nre 's/modules:(.*)/\1/p')
	for var in "$@"; do unset val _val
		case $var in
		relos)
			_val=$(echo "$target" | sed -nre 's/relocatable objects:(.*)/\1/p')
			for each in $_val; do val="${val:+$val }${mod}/${each}"; done
		;;
		execs)
			_val=$(echo "$target" | sed -nre 's/executable objects:(.*)/\1/p')
			for each in $_val; do val="${val:+$val }${mod}/${each}"; done
		;;
		stlibs)
			_val=$(echo "$target" | sed -nre 's/static libraries:(.*)/\1/p')
			for each in $_val; do val="${val:+$val }${mod}/${each}"; done
		;;
		shlibs)
			_val=$(echo "$target" | sed -nre 's/shared libraries:(.*)/\1/p')
			for each in $_val; do val="${val:+$val }${mod}/${each}"; done
		;;
		esac
		for _mod in ${mods}; do val=${val:+$val }$(mod_target $mod/$_mod $((dep + 1)) $var); done
		[ -n "$val" ] && echo "$val"
	done
}

mod=$1; shift
mod_target $mod 0 "$@"