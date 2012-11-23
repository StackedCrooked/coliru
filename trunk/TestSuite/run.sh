#!/bin/bash
if [[ `whoami` == "root" ]] ; then
	echo "This script should not be run as root." >&1
	exit 1
fi

for dir in `ls` ; do
	echo `pwd`
	cd $dir && ../../Web/sandbox.sh 2>&1
	cd - 
done
