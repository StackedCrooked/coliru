#!/bin/bash
if [[ `whoami` == "root" ]] ; then
	echo "This script should not be run as root." >&1
	exit 1
fi

BASEDIR=`pwd`
LIST=`ls`
echo "LIST: ${LIST}"

for dir in $LIST ; do
	cd $dir
	echo "< `pwd` >"
	../../Web/sandbox.sh 2>&1 || true
	cd $BASEDIR
	echo "</ `pwd` >"
done
