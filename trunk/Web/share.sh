#!/bin/bash
source coliru_env.source
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }
pkill -9 -u sandbox
./repair-permissions.sh >/dev/null 2>&1

mkdir -p ${COLIRU_ARCHIVE}
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum main.cpp | cut -d ' ' -f 1)"
fi

if [ -d "${COLIRU_ARCHIVE}/${ID}" ] ; then
    echo "ID=${ID}"
    exit
fi

DIR="${COLIRU_ARCHIVE}/${ID}"
mkdir "${DIR}"

cat main.cpp > "${DIR}/main.cpp"
echo "ID=${ID}"
echo "Operation timed out." > "${DIR}/output"
./build_and_run.sh >"${DIR}/output.tmp" 2>&1 && mv "${DIR}/output.tmp" "${DIR}/output"
