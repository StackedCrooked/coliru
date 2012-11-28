#!/bin/bash
mkdir -p Archive
if [ "$(uname)" == "Darwin" ] ; then 
    ID="$(md5 main.cpp | cut -d '=' -f 2 | sed -e 's/ //g')"
else
    ID="$(md5sum main.cpp | cut -d ' ' -f 1)"
fi

if [ -d "Archive/${ID}" ] ; then
    echo ${ID}
    exit
fi

DIR="Archive/${ID}"
mkdir "${DIR}"

cat main.cpp > "${DIR}/main.cpp"

ulimit -f 100
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
{ { sleep 10 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; { ./chroot.sh >"${DIR}/output" 2>&1 ; } ; echo ${ID} ;  exit 0 ; }

