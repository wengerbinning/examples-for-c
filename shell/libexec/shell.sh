#!/usr/bin/env bash

PROG=${0##*/}
DATE="2023-08-29"
VERSION="v0.0.0.1"
CMD="help"
CMD_LOCK=false
VERBOSE=false
unset LABEL SERVER
#-----------------------------------------------------------------------------
HELP=$(cat <<EOF
 $PROG is a shell script tool framework.
 
 USAGE:
	$PROG [OPTIONS] [COMMANDS]

 COMMAND:
	-h, --help
	-V, --version

 EXTISTIONS:
 	--push
	--pull
	--archive

 OPTIONS:
 	-l, --label
	-v, --verbose
	-s, --server

 EXAMPLES:
	-0- $PROG --help
	-0- $PROG --version
	-0- $PROG --verbose --help
	-1- $PORG --verbose --version

EOF
)


##############################################################################

#-----------------------------------------------------------------------------
# usage: help [<prog>]
help() {
	echo -e "$HELP"
}

#-----------------------------------------------------------------------------
# usage: version [<prog>]
version() {
	echo "Version:$VERSION($DATE)"
}

#-----------------------------------------------------------------------------
# usage: main 
main() {
	case $CMD in
	help)
		help; return
	;;
	version)
		version; return
	;;

	esac
}
##############################################################################
#
idx=0
while test -n "$1"; do cmd=$1; shift; idx=$((idx + 1))
	[ "$DEBUG" = true ] && {
		echo "$idx $cmd"
	}
    case $cmd in
    -h|--help)
        CMD="help"
		CMD_LOCK=true
	;;
	-l|--label)
		LABEL=$1; shift
    ;;
    -V|--version)
        test "$CMD_LOCK" == true || CMD="version"
        CMD_LOCK=true
    ;;
    -v|--verbose)
        VERBOSE=true
    ;;
    esac
done

[ "$VERBOSE" == true ] && {
	echo "CURRENT COMMAND: $CMD"
	echo "VERBOSE ATTR: $VERBOSE"
	echo "LABEL ATTR: $LABEL"
}
#
main "$@"
