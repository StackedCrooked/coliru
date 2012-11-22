set -x
MYPID=$$
echo "MYPID: $MYPID"
cp main.cpp /chroot/user/main.cpp
cp build.sh /chroot/user/build.sh

# Schedule timeout
{ { sleep 5 && echo "Timeout" 1>&2 ; /bin/bash -c "kill -9 ${MYPID}" ; } & } && { trap "kill $!" INT ERR EXIT && { chroot /chroot bash coliru >output; } || { echo "User command was terminated." 1>&2 ; } ; }
