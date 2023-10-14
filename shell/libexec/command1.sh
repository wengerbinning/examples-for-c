#!/bin/bash

PROG=${0##*/}
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
#-----------------------------------------------------------------------------
[ $(echo "\n" | wc -l) -eq 1 ] && 

alias echa='echo -e'

echa "\n"

##############################################################################
# usage: error [<mode>] <message>
error() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }; _mod=${_mod:-$MODULE}
    echo "${_mod:+$_mod.}\e[31merror\e[0m: $@"
}
# usage: warning [<mode>] <message>
warning() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }; _mod=${_mod:-$MODULE}
    echo "${_mod:+$_mod.}\e[33mwarning\e[0m: $@"
}
# usage: notice [<mode>] <message>
notice() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }; _mod=${_mod:-$MODULE}
    [ "$VERBOSE" == true ] || return
    echo "${_mod:+$_mod.}\e[35mnotice\e[0m: $@"
}
# usage: info [<mode>] <message>
info() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }; _mod=${_mod:-$MODULE}
    [ "$VERBOSE" == true ] || return
    echo "${_mod:+$_mod.}\e[32minfo\e[0m: $@"
}
# usage: debug [<mode>] <message>
debug() {
    local _mod
    [ $# -gt 1 ] && { _mod=$1; shift 1; }; _mod=${_mod:-$MODULE}
    test "$DEBUG" || return
    echo "${_mod:+$_mod.}\e[34mdebug\e[0m: $@"
}

#------------------------------------------------------------------------------
# usage: cmd_help [<module>]
cmd_help() {
	echo "$HELP"
}

#-----------------------------------------------------------------------------
# usage: cmd_versoin [<module>]
cmd_versoin() {
	echo "Version:$VERSION($DATE)"
}

#-----------------------------------------------------------------------------
# usage: main 
main() {
    debug "$@"
}

##############################################################################
## PARSING COMMAND PARAMETER
_idx=0
while test -n "$1"; do _opt=$1; shift; _idx=$((_idx + 1))
    debug param "Parsing $_idx："$_opt" parameter ..."
    case $_opt in
    -h|--help)
        test -n "$MOD" && _mod=$MOD; cmd_help ${_mod:-$MODULE}; exit
    ;;
    -v|--verbose)   
        VERBOSE=true
    ;;
    -V|--version)
        test -n "$MOD" && _mod=$MOD; cmd_version ${_mod:-$MODULE}; exit
    ;;
    --debug)
        DEBUG=true
    ;;
    --)
        break;;
    --*)
        error param "Unknown parameter: $_opt"
        cmd_help; exit
    esac
done
## DEBUG FOR PARAMETER
debug param "VERBOSE: $VERBOSE"
debug param "DEBUG: $DEBUG (${DBG_MOD:-all})"
# START THE MAIN TASK
main "$@"
