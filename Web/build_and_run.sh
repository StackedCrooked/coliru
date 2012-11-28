

ulimit -f 1000
rm -rf /var/chroot/tmp/*
set -e
[ -f main.cpp ] || { echo "Webserver could not find main.cpp. Exiting." >2 ; exit 1; }
cp compile.sh main.cpp /var/chroot/tmp

# Run the chroot
{ { sleep 10 && echo "Timeout!" && { pkill -9 -u sandbox >/dev/null 2>&1  ; } && exit 1 ; } & } && { trap "kill $! >/dev/null 2>&1" INT ERR EXIT; { ./chroot.sh >"${DIR}/output" 2>&1 ; } ; echo ${ID} ;  exit 0 ; }

