#!/usr/bin/env bash


PROG=${0##*/}
DATE="2023-08-29"
VERSION="v0.0.0.1"
CMD="help"
CMD_LOCK=false
VERBOSE=false


#-----------------------------------------------------------------------------

HELP=$(cat <<EOF
 $PROG is a shell script tool framework.
 
 USAGE:
	$PROG [OPTIONS] [COMMANDS]

 COMMAND:
	-h, --help
	-V, --version

 OPTIONS:
	-v, --verbose

EOF
)


##############################################################################

# usage: help [<prog>]
help() {
	echo -e "$HELP"
}

# usage: version [<prog>]
version() {
	echo "Version:$VERSION($DATE)"
}

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
while test -n "$1"; do
    case $1 in
    -h|--help)
        CMD="help"
		CMD_LOCK=true
    ;;
    -V|--version)
        test "$CMD_LOCK" == true || CMD="version"
        CMD_LOCK=true
    ;;
    -v|--verbose)
        VERBOSE=true
    ;;
    esac
shift; done

[ "$VERBOSE" == true ] && echo "CMD:$CMD"
#
main "$@"
