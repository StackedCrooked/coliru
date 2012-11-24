NPROC_LIMIT=`ulimit -a 2>&1 | grep "\-u" | awk '{print $5}'`
[ ${NPROC_LIMIT} -lt 200 ] || { echo "NPROC limit is too high: ${NPROC_LIMIT}. Exiting." >&2 ; exit 1 ; }
ulimit -t 1
ulimit -n 20
cp main.cpp /var/chroot/home/lol/main.cpp
echo "cd /home/lol && bash main.cpp" >/var/chroot/home/lol/build.sh
chroot /var/chroot bash /home/lol/build.sh
