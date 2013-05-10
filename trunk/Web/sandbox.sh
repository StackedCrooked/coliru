#!/bin/bash
set -e
source coliru_env.source


[ "$TMP_DIR" == "" ] && { echo "TMP_DIR not set." 1>&2 ; exit 1 ; }

if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 ${TMP_DIR}/main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')-$(md5 ${TMP_DIR}/cmd.sh | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum ${TMP_DIR}/main.cpp | cut -d ' ' -f 1)-$(md5sum ${TMP_DIR}/cmd.sh | cut -d ' ' -f 1)"
fi

if [ -f "${COLIRU_ARCHIVE}/${ID}/output" ] ; then
    cat "${COLIRU_ARCHIVE}/${ID}/output"
    exit
fi

trap "rm -f timeout.txt; exit" INT TERM EXIT

#pkill -9 -u sandbox

#{ ./repair-permissions.sh >/dev/null 2>&1 ; } || true
./build_and_run.sh
