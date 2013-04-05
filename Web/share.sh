#!/bin/bash
source coliru_env.source
[ -d ${COLIRU_ARCHIVE} ] || { echo "${COLIRU_ARCHIVE} does not exist. Exiting." && exit 1 ; }
pkill -9 -u sandbox
./repair-permissions.sh >/dev/null 2>&1

mkdir -p ${COLIRU_ARCHIVE}
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')-$(md5 cmd.sh | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum main.cpp | cut -d ' ' -f 1)-$(md5sum cmd.sh | cut -d ' ' -f 1)"
fi

echo "${ID}"

if [ -d "${COLIRU_ARCHIVE}/${ID}" ] ; then
    exit
fi

DIR="${COLIRU_ARCHIVE}/${ID}"
mkdir "${DIR}"

cat main.cpp > "${DIR}/main.cpp"
cat cmd.sh > "${DIR}/cmd.sh" ;

chmod 755 "${DIR}/cmd.sh"

{ ./build_and_run.sh >"${DIR}/output" 2>&1 ; } || true

