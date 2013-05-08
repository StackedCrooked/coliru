#!/bin/bash

# Launcher script that ensures there is only one instance of the launched
# script running.
#
# Usage examples:
#  ./singleton.sh ./user_script.sh
#  ./singleton.sh echo hello
#
# The trick here is the kill -0 which doesn't deliver any signal but just
# checks if a pid is running. Also the call to trap will ensure that the
# lockfile is removed even when your process is killed (except kill -9).
#
# http://stackoverflow.com/questions/185451/quick-and-dirty-way-to-ensure-only-one-instance-of-a-shell-script-is-running-at


COMMAND_MD5=$(echo "$@" | md5sum - | cut -d ' ' -f1)
LOCKFILE="/tmp/${COMMAND_MD5}"
if [ -e ${LOCKFILE} ] && kill -0 `cat ${LOCKFILE}`; then
    echo "already running"
    exit
fi

# make sure the lockfile is removed when we exit and then claim it
trap "rm -f ${LOCKFILE}; exit" INT TERM EXIT
echo $$ > ${LOCKFILE}

# run user program
$@

rm -f ${LOCKFILE}
