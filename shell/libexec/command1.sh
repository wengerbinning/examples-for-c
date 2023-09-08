#!/bin/sh

PROG=${0}
DATE="2023-08-29"
VERSION="v0.0.0.1"
VERBOSE=false
DEBUG=false
#-----------------------------------------------------------------------------
HELP=$(cat <<EOF
 $PROG is a shell script tool framework.
 
 USAGE:
	$PROG [OPTIONS]

 OPTIONS:
	-h, --help
	-v, --verbose
    -V, --version

 EXAMPLES:
	- $PROG --help
	- $PROG --version

EOF
)

##############################################################################
# usage: error [<mode>] <message>
error() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }
    _mod=${_mod:-$MODULE}
    echo -e "${_mod:+$_mod.}\e[31merror\e[0m: $@"
}

# usage: warning [<mode>] <message>
warning() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }
    _mod=${_mod:-$MODULE}
    echo -e "${_mod:+$_mod.}\e[33mwarning\e[0m: $@"
}
# usage: notice [<mode>] <message>
notice() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }
    _mod=${_mod:-$MODULE}
    [ $VERBOSE == true ] || return
    echo -e "\e[35m${_mod:+$_mod.}notice\e[0m: $@"
}
# usage: info [<mode>] <message>
info() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }
    _mod=${_mod:-$MODULE}
    [ $VERBOSE == true ] || return
    echo -e "\e[32m${_mod:+$_mod.}info\e[0m: $@"
}
# usage: debug [<mode>] <message>
debug() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }
    _mod=${_mod:-$MODULE}
    [ $DEBUG == true ] || return
    echo -e "${_mod:+$_mod.}\e[34mdebug\e[0m: $@"
}

#------------------------------------------------------------------------------
# usage: cmd_help [<prog>]
cmd_help() {
	echo -e "$HELP"
}
#-----------------------------------------------------------------------------
# usage: cmd_versoin [<prog>]
cmd_versoin() {
	echo "Version:$VERSION($DATE)"
}

#-----------------------------------------------------------------------------
# usage: main 
main() {
    return
}
##############################################################################
## Command parameter parsing
idx=0
while test -n "$1"; do opt=$1; shift; idx=$((idx + 1))
    debug param "Parsing $idx：$opt parameter ..."
    case $opt in
    -h|--help)
        cmd_help
        exit
	;;
    -v|--verbose)
        VERBOSE=true
    ;;
    -V|--version)
        test "$CMD_LOCK" == true || CMD="version"
        CMD_LOCK=true
    ;;
    --debug)
        DEBUG=true
    ;;
    *)
        error param "Unknown parameter: $opt"
        cmd_help
        exit
    esac
done
## Parameter debugger
debug param "VERBOSE: $VERBOSE"
debug param "DEBUG: $DEBUG"
debug param "DEBUG MODEULE: ${DBG_MOD:-all}"
#
main "$@"
