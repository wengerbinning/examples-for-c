#!/usr/bin/env bash

# =========================================================================== #

#
error() {
	echo -en "\e[31m"; echo $@; echo -en "\e[0m"
}
#
warning() {
	echo -en "\e[33m"; echo $@; echo -en "\e[0m"
}
#
notice() {
	echo -en "\e[32m"; echo $@; echo -en "\e[0m"
}
#
note() {
	echo -en "\e[34m"; echo $@; echo -en "\e[0m"
}
#
debug() {
	echo -en "\e[32m"; echo $@; echo -en "\e[0m"
}
#
run_cmd() {
	local ret
	eval "time $@"; ret=$?
	test ${ret:-1} -ne 0 && {
		error "running command error($ret)!"
		debug "command:$@"
		exit $ret
	}
}

# =========================================================================== #

unset WFINIT WFCNT
WORKFLOW="Generial Workflow Task"

# --------------------------------------------------------------------------- #
#
workflow_init() {
	local idx work func
	#
	test -f ".workflow" || {
		#
		notice "Start ${WORKFLOW:-Generial Workflow Task} ..."
		#
		while [ ${idx:-0} -lt ${WFINIT:-0} ]; do
			eval "func=\${wfinit${idx:-0}_func}"
			test -n "$func" && eval "$func"
		idx=$((idx + 1)); done
	}
	touch .workflow
	echo "WORKFLOW PHASE:0/${WFCNT:-0}" > .workflow
}

#
workflow_add() {
	local func type
	#
	case ${#:-0} in
	1) func=${1} ;;
	2) type=${1}; func=${2} ;;
	*) return
	esac
	#
	case ${type:-unknown} in
	init)
		eval "wfinit${WFINIT:-0}_func=\"$func\""
		WFINIT=$((WFINIT + 1))
		return 
	;;
	esac
	#
	eval "workflow${WFCNT:-0}_func=\"$func\""
	WFCNT=$((WFCNT + 1))
}

#
workflow_next() {
	sed -i -rne "s/WORKFLOW PHASE:([0-9]*)\/([0-9]).*/WORKFLOW PHASE:${1:-0}\/\2/p" .workflow
}

#
workflow_exit() {
	notice Finish ${WORKFLOW:-Generial Workflow Task}.
	rm -rf .workflow
}

#
workflow_running() {
	local srt_time cur_time idx func
	srt_time=$(date +%s)
	#
	test -f .workflow || workflow_init
	idx=$(sed -rne 's/WORKFLOW PHASE:([0-9]*)\/([0-9]).*/\1/p' .workflow)
	#
	eval "work=\${workflow${idx:-0}_work}"
	eval "func=\${workflow${idx:-0}_func}"
	work=${work:-$func}
	#
	test -n "$func" && eval "$func"
	#
	idx=$((idx + 1))
	cur_time=$(date +%s)
	notice Runing workflow  $idx:${work:-null} use $((cur_time -srt_time)) second.	
	test ${idx:-0} -ge ${WFCNT:-0} && workflow_exit || workflow_next $idx
}

# =========================================================================== #


# =========================================================================== #

workflow_running