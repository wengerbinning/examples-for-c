#!/usr/bin/env bash

# =========================================================================== #

CMD_LOG_HOME=".command"
# --------------------------------------------------------------------------- #
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
	local ret file
	file="${CMD_LOG_HOME}/$(date +%s).log"
	test -d "${CMD_LOG_HOME}" || mkdir -p ${CMD_LOG_HOME}
	test -f $file && cp $file "${file}.old"
	echo "[$(date +"%Y/%m/%d %H:%M:%S %z")] ${PWD} # $@" > $file
	eval "$@  2>&1 | tee $file"; ret=$?
	test ${ret:-1} -ne 0 && {
		error "running command error($ret)!"
		debug "command:$@"
		exit $ret
	}
}

# =========================================================================== #

unset WFINIT WFEXIT WFCNT
WORKFLOW_DESC="Generial Workflow Task"
WORKFLOW_PAUSE=false
WORKFLOW_FORCE=false
WORKFLOW_BASE=${PWD}
WORKFLOW_HOME="${WORKFLOW_BASE}/.workflow"

# --------------------------------------------------------------------------- #

# usage: _workflow_init
_workflow_init() {
	local idx work func normal=${1:-true}
	test -d "${WORKFLOW_HOME}" || {
		mkdir ${WORKFLOW_HOME} || { error "create ${WORKFLOW_HOME} failed!"; return 255; }
		echo "WORKFLOW PHASE:0/${WFCNT:-0}" > ${WORKFLOW_HOME}/stat
		case ${normal:-true} in
		true) notice "Start ${WORKFLOW_DESC:-Generial Workflow Task} ..." ;;
		*)    notice "Init ${WORKFLOW_DESC:-Generial Workflow Task} ..."
		esac
		while [ ${idx:-0} -lt ${WFINIT:-0} ]; do
			eval "func=\${wfinit${idx:-0}_func}"
			test -n "$func" && eval "$func"
		idx=$((idx + 1)); done
	}
}


# usage: _workflow_next
_workflow_next() {
	sed -i -rne "s/WORKFLOW PHASE:([0-9]*)\/([0-9]).*/WORKFLOW PHASE:${1:-0}\/\2/p" ${WORKFLOW_HOME}/stat
}

# usage: __workflow_exit <>
_workflow_exit() {
	local idx func normal=${1:-true}
	case ${normal:-true} in
	true) notice "Finish ${WORKFLOW:-Generial Workflow Task}." ;;
	*)    notice "Exit ${WORKFLOW:-Generial Workflow Task}."
	esac
	while [ ${idx:-0} -lt ${WFEXIT:-0} ]; do
		eval "func=\${wfexit${idx:-0}_func}"
		test -n "$func" && eval "$func"
	idx=$((idx + 1)); done
	rm -rf ${WORKFLOW_HOME}
}

# usage: workflow_add
workflow_add() {
	local func type
	case ${#:-0} in
	1) func=${1} ;;
	2) type=${1}; func=${2} ;;
	*) return
	esac
	case ${type:-unknown} in
	init)
		eval "wfinit${WFINIT:-0}_func=\"$func\""
		WFINIT=$((WFINIT + 1))
		return
	;;
	exit)
		eval "wfexit${WFEXIT:-0}_func=\"$func\""
		EXIT=$((WFEXIT + 1))
		return
	;;
	esac
	eval "workflow${WFCNT:-0}_func=\"$func\""
	WFCNT=$((WFCNT + 1))
}

# usage: workflow_running
workflow_running() {
	local srt_time cur_time idx func
	srt_time=$(date +%s)
	[ "${WORKFLOW_FORCE:-false}" == "true" ] && _workflow_exit false
	test -d ${WORKFLOW_HOME} || _workflow_init
	case ${WORKFLOW_PAUSE:-false} in
	true)
		idx=$(sed -rne 's/WORKFLOW PHASE:([0-9]*)\/([0-9]).*/\1/p' .workflow/stat)
		CMD_LOG_HOME="${WORKFLOW_HOME}/${srt_time}/$idx"
		eval "work=\${workflow${idx:-0}_work}"
		eval "func=\${workflow${idx:-0}_func}"
		work=${work:-$func}
		oldcwd=${PWD}
		test -n "$func" && eval "$func"
		cd $oldcwd
		idx=$((idx + 1))
		cur_time=$(date +%s)
		notice Runing workflow  $idx:${work:-null} use $((cur_time - srt_time)) second.
		test ${idx:-0} -ge ${WFCNT:-0} && _workflow_exit || _workflow_next $idx
	;;
	*)
		while [ ${idx:-0} -lt ${WFCNT:-0} ]; do
			CMD_LOG_HOME="${WORKFLOW_HOME}/${srt_time}/$idx"
			eval "work=\${workflow${idx:-0}_work}"
			eval "func=\${workflow${idx:-0}_func}"
			work=${work:-$func}

			test -n "$func" && eval "$func"

			idx=$((idx + 1));
			cur_time=$(date +%s)
			notice Runing workflow  $idx:${work:-null} use $((cur_time - srt_time)) second.
		done
	esac
}

# =========================================================================== #

WORKFLOW_DESC="GWN/GCC Firmware Build Workflow"
BRANCH="master"
VERSION="0.0.0.1"
RELEASED="/srv/grandstream/released"

# --------------------------------------------------------------------------- #

workflow_add init workflow_init
workflow_init() {
	local cur_branch
	#
	test -f ${WORKFLOW_BASE}/image_build/gwn_firmware_private || {
		cd ${WORKFLOW_BASE}/image_build && {
			openssl genrsa -out gwn_firmware_private 2048
			cd - >/dev/null
		}
	}
	#
	test -f ${WORKFLOW_BASE}/image_build/gs_local.pem || {
		cd ${WORKFLOW_BASE}/public && {
			./create_certs.py --product gcc601x
			cd - >/dev/null
		}
	}
	#
	cd "$WORKFLOW_BASE/image_build" && {
		cur_branch=$(git branch | grep -e '*' | cut -d' ' -f2)
		cur_branch=${cur_branch#*/}; cur_branch=${cur_branch%/*};
		BRANCH=${cur_branch//[-\/]/}
		cd - >/dev/null
	}
	echo "$BRANCH" > $WORKFLOW_HOME/branch
}

#
workflow_add workflow0
workflow0() {
	local version branch
	local ver_major ver_minor ver_phase ver_patch prefix

	test -f ${WORKFLOW_HOME}/branch && branch=$(cat ${WORKFLOW_HOME}/branch 2>/dev/null)
	test -f ${WORKFLOW_HOME}/version && version=$(cat ${WORKFLOW_HOME}/version 2>/dev/null)
	branch=${branch:-$BRANCH}
	version=${version:-$VERSION}
	ver_major=$(echo $version | cut -d'.' -f1)
	ver_minor=$(echo $version | cut -d'.' -f2)
	ver_phase=$(echo $version | cut -d'.' -f3)
	ver_patch=$(echo $version | cut -d'.' -f4)

	prefix=$(printf "%02d/%d" ${ver_phase:-0} $((ver_patch /10)))
	released="${RELEASED}/${branch}/v${ver_major}.${ver_minor}/$prefix/v$version"

	rm -f $(tree -L 1 -iaFf ${RELEASED} | grep '.bin$' | xargs)

	VERSION=$version
	CUR_RELEASED=$released
	export VERSION CUR_RELEASED
}

#
workflow_add workflow1
workflow1() {
	#
	work1() {
		local famil=$1
		local version=$2
		local released=$3
		local firmware=$4

		notice "Start Work for ${famil} ${version} to ${released} ..."
		test -z "$firmware" && firmware="${famil}fw.bin"
		#
		cd ${WORKFLOW_BASE}/image_build && {
			run_cmd ${WORKFLOW_BASE}/image_build/genimage ${famil} --version ${version}
			cd - >/dev/null
		}
		#
		test -d ${released} || mkdir -p ${released}
		run_cmd cp -rf ${WORKFLOW_BASE}/image_build/build/${famil} ${released}/${famil}
		run_cmd cp  -f ${released}/${famil}/images/prod/${firmware}  ${released}/${firmware}
		run_cmd cp  -f ${released}/${famil}/images/prod/${firmware}  ${RELEASED}/${firmware}
	}





	work1 gwn7062  ${VERSION} ${CUR_RELEASED}
	work1 gwn7052  ${VERSION} ${CUR_RELEASED}
	cp ${RELEASED}/gwn7052fw.bin ${RELEASED}/gwn7052ffw.bin
	work1 gwn700x  ${VERSION} ${CUR_RELEASED}
	work1 gwn7062e ${VERSION} ${CUR_RELEASED}
	work1 gcc601x  ${VERSION} ${CUR_RELEASED}
}

#
workflow_add workflow2
workflow2() {
	local version ver_major ver_minor ver_phase ver_patch
	version=${version:-$VERSION}
	ver_major=$(echo $version | cut -d'.' -f1)
	ver_minor=$(echo $version | cut -d'.' -f2)
	ver_phase=$(echo $version | cut -d'.' -f3)
	ver_patch=$(echo $version | cut -d'.' -f4)
	#
	ver_patch=$((ver_patch + 1))
	version=${ver_major:-0}.${ver_minor:-0}.${ver_phase:-0}.${ver_patch:-0}
	echo $version > ${WORKFLOW_HOME}/version
}

# =========================================================================== #

script_help() {
cat <<EOF
workflow - This is a work flow tools.

workflow [OPTIONS] [COMMANDS]

OPTIONS:
	-f, --force
	-v, --verbose
	-h, --help
	-p, --pause
	-V, --version

EOF
}

script_version() {
cat <<EOF
workflow: v0.0.0.1
EOF
}

# =========================================================================== #

for var in "$@"; do
case ${var:---help} in
--help)
	script_help
	exit ;;
--version)
	script_version
	exit ;;
-f|--force)
	WORKFLOW_FORCE=true ;;
-p|--pause)
	WORKFLOW_PAUSE=true ;;
esac
done

workflow_running



