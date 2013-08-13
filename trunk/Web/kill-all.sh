PGID="$(ps -eopgid,ppid,pid,comm | grep 'restart.sh' | awk '{print $1}')"
if [ "${PGID}" != "" ] ; then
    echo "Killing pgid ${PGID}"
    kill -9 -${PGID}
else
    echo "restart.sh does not seem to be running." 1>&2 ; exit 1
fi
