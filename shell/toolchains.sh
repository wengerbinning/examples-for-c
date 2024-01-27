#!/usr/bin/env bash

#
test "$0" = "$SHELL" && __name__="__source__" || __name__="__main__"

#
VARIABLERC_DEFAULT='.variablerc'
TOOLCHAIN_HOME_DEFAULT="/opt/toolchains"
TOOLCHAIN_ENVIRONMENT_DEFAULT="environment"

# ============================================================================ #

error() {
	echo -ne "\e[31m"
	echo -ne "$@"
	echo -ne "\e[0m"
	echo -ne "\n"
}

warning() {
	echo -ne "\e[33m"
	echo -ne "$@"
	echo -ne "\e[0m"
	echo -ne "\n"
}

info() {
	echo -ne "\e[34m"
	echo -ne "$@"
	echo -ne "\e[0m"
	echo -ne "\n"
}

debug() {
	echo -ne "\e[32m"
	echo -ne "$@"
	echo -ne "\e[0m"
	echo -ne "\n"
}

# ---------------------------------------------------------------------------- #

# usage: variable_init
variable_init() {
	local variablerc=${VARIABLERC:-$VARIABLERC_DEFAULT}
	#
	unset DVAR_TABLE # Default Variable Table
	unset IVAR_TABLE # Insert Variable Table
	unset OVAR_TABLE # Override Variable Table
	#
	unset IMVAR_TABLE # Import Variable
	unset EXVAR_TABLE # Export Variable
	#
	rm -rf $variablerc
}

#usage: variable_import <variable>...
variable_import() {
	local var val
	for var in "$@"; do
		eval val="\$${var}"
		test -n "$val" || {
			error "Not found variable:$var! Please Set $var before running.";
			return 1;
		}
		IMVAR_TABLE="${IMVAR_TABLE:+$IMVAR_TABLE }$var"
	done
}

# usage: variable_default <variable> <value>
variable_default() {
	local val var=$1; shift
	local variablerc=${VARIABLERC:-$VARIABLERC_DEFAULT}
	eval "val=\$${var}"; val="${val:-$@}"
	eval "$var=\"$val\""
	echo "$var=\"$val\"" >> $variablerc
	DVAR_TABLE="${DVAR_TABLE:+$DVAR_TABLE }$var"
}

# usage: variable_insert <separator> <variable> <value>
variable_insert() {
	local chr=${1:0:1} var=$2 val val1=$3 val2
	local variablerc=${VARIABLERC:-$VARIABLERC_DEFAULT}
	eval "val=\$${var}"
	test -n "$val" && {
		val2="$(eval echo $val | awk -v "val=$val1" -F$chr \
			'{for (i=1; i<= NF; i++) {if ( val == $i ) {printf "%s", val }}}')"
		test -n "$val2" && warning "Found $val2 in variable:$var, so will be skiped!"
	} || {
		val="$val1${val:+$chr$val}"
		eval "$var=\"$val\""
	}
	echo "$var=\"$val\"" >> $variablerc
	IVAR_TABLE="${IVAR_TABLE:+$IVAR_TABLE }$var"
}

# usage: variable_override <variable> <value>
variable_override() {
	local val var=$1; shift
	local variablerc=${VARIABLERC:-$VARIABLERC_DEFAULT}
	eval "val=\$${var}"
	test -n "$val" && warning "The $var already has a value:$val, which will be overwritten!"
	val=$@; eval "$var=\"$val\""
	echo "$var=\"$val\"" >> $variablerc
	OVAR_TABLE="${OVAR_TABLE:+$OVAR_TABLE }$var"
}

# usage: variable_export <variable>...
variable_export() {
	local var val
	local variablerc=${VARIABLERC:-$VARIABLERC_DEFAULT}
	for var in "$@"; do
		eval "val=\$${var}"
		test -n "$val" || {
			warning "The $var is None!"
		}
		export $var

		EXVAR_TABLE=${EXVAR_TABLE:+$EXVAR_TABLE }$var
	done
	echo "export $@" >> $variablerc
}

# usage: variable_commit
variable_commit() {
	DVAR_TABLE=$(echo $DVAR_TABLE | tr -s ' ' '\n' | sort | uniq | xargs)
	IVAR_TABLE=$(echo $IVAR_TABLE | tr -s ' ' '\n' | sort | uniq | xargs)
	OVAR_TABLE=$(echo $OVAR_TABLE | tr -s ' ' '\n' | sort | uniq | xargs)
	IMVAR_TABLE=$(echo $IMVAR_TABLE | tr -s ' ' '\n' | sort | uniq | xargs)
	EXVAR_TABLE=$(echo $EXVAR_TABLE | tr -s ' ' '\n' | sort | uniq | xargs)
}

# usage: variable_dump
variable_dump() {
	local var val
	#
	debug "-----------------------------------------------------------------"
	debug "###################### Dump Variable Table ######################"
	debug "-----------------------------------------------------------------"
	#
	debug "Import Variable Table: $IMVAR_TABLE"
	for var in $IMVAR_TABLE; do
		eval "val=\$${var}"
		info " - $var=$val"
	done
	#
	debug "Default Variable Table: $DVAR_TABLE"
	for var in $DVAR_TABLE; do
		eval "val=\$${var}"
		info " - $var=$val"
	done
	#
	debug "Insert Variable Table: $IVAR_TABLE"
	for var in $IVAR_TABLE; do
		eval "val=\$${var}"
		info " - $var=$val"
	done
	#
	debug "Overiade Variable Table: $OVAR_TABLE"
	for var in $OVAR_TABLE; do
		eval "val=\$${var}"
		info " - $var=$val"
	done
	#
	debug "Export Variable Table: $EXVAR_TABLE"
	for var in $EXVAR_TABLE; do
		eval "val=\$${var}"
		info " - $var=$val"
	done
}

# ---------------------------------------------------------------------------- #

# usage: environment_import <environment>
environment_import() {
	local environment=$1
	test -f $environment || {
		error "The $environment environment file does not exist!";
		return 1;
	}
	local environment_name=$(basename $environment)
	local environment_home=$(cd $(dirname $environment) && pwd)
	environment=$environment_home/$environment_name
	#
	toolchain_default=$(basename $environment_home)
	toolchains_default=$(dirname $environment_home)
	TOOLCHAIN=${TOOLCHAIN:-$toolchain_default}
	TOOLCHAINS=${TOOLCHAINS:-$toolchains_default}
	#
	variable_init
	#
	while read line; do
		line=$(echo $line | tr -s ' ')
		test -n "$line" || continue
		#
		prefix=$(echo $line | cut -c 1)
		case $prefix in
		'#')
			continue;;
		esac
		#
		key=$(echo "$line" | cut -d' ' -f1)
		case $key in
		import)
			table=$(echo "$line" | cut -d' ' -f2-)
			variable_import $table || { exit 2; }
			continue;;
		export)
			table=$(echo "$line" | cut -d' ' -f2-)
			variable_export $table || { exit 2; }
			continue;;
		esac
		#
		var=$(echo "$line" | sed -nre 's/^(.*)(.=)(.*)$/\1/p')
		opt=$(echo "$line" | sed -nre 's/^(.*)(.=)(.*)$/\2/p')
		val=$(echo "$line" | sed -nre 's/^(.*)(.=)(.*)$/\3/p')
		case $opt in
		'?=')
			eval "variable_default $var $val";;
		'='|':=')
			eval "variable_override $var $val";;
		'+=')
			eval "variable_insert ':' $var $val";;
		esac
		#
	done < $environment
	#
	variable_commit
	#
	printenv > .env
}

# ---------------------------------------------------------------------------- #

# usage: toolchain_init
toolchain_init() {
	local home=${1:-$TOOLCHAIN_HOME_DEFAULT}
	local environment=${2:-$TOOLCHAIN_ENVIRONMENT_DEFAULT}
	local dir toolchain
	unset TOOLCHAIN_TABLE # TOOLCHAIN TABLE
	unset TOOLCHAIN_COUNT # TOOLCHAIN COUNT
	#
	for dir in $(find $home -mindepth 1 -maxdepth 1 -type d 2>/dev/null); do
		dir=$(cd $dir && pwd)
		test -f $dir/$environment || continue
		toolchain=$dir
		TOOLCHAIN_TABLE=${TOOLCHAIN_TABLE:+$TOOLCHAIN_TABLE }$toolchain
		TOOLCHAIN_COUNT=$((TOOLCHAIN_COUNT + 1))
	done
	TOOLCHAIN_TABLE=$(echo $TOOLCHAIN_TABLE | tr -s ' ' '\n' | sort | uniq | xargs)
}

# usage: toolchain_dump
toolchain_dump() {
	local toolchain idx total=$TOOLCHAIN_COUNT
	for toolchain in $TOOLCHAIN_TABLE; do idx=$((idx + 1))
		debug "$idx/$total - $toolchain"
	done
}

# usage: toolchain_check
toolchain_check() {
	local toolchain=$1
	test -n "$toolchain" || return 1
	for each in $TOOLCHAIN_TABLE; do
		test "$each" == "$toolchain" && return
	done
	return 1
}

# usage: toolchain_source <toolchain>
toolchain_source() {
	local toolchain=$1

	local environment=${TOOLCHAIN_ENVIRONMENT:-$TOOLCHAIN_ENVIRONMENT_DEFAULT}
	variablerc="$(pwd)/$variablerc"
	toolchain_check $toolchain || return 1
	environment_import $toolchain/$environment

}

# ---------------------------------------------------------------------------- #

source_commit() {
	local variablerc=${VARIABLERC:-$VARIABLERC_DEFAULT}

	source $variablerc
	#
	unset __name__
	unset VARIABLERC_DEFAULT TOOLCHAIN_HOME_DEFAULT
	unset TOOLCHAIN_ENVIRONMENT_DEFAULT
	unset error warning notice info
	unset debug
	#
	unset variable_init variable_commit variable_dump
	unset variable_import variable_export
	unset variable_default variable_insert variable_override
	#
	unset environment_import
	#
	unset toolchain_init
	unset toolchain_dump toolchain_check toolchain_source
	#
	unset source_commit
}


# ============================================================================ #

toolchain_init

case $__name__ in
__main__)
	toolchain_dump
;;
__source__)
	toolchain_source /opt/toolchains/toolchain-aarch64_cortex-a53_gcc-8.4.0_musl
	source_commit
;;
esac