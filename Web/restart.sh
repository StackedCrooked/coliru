#!/bin/bash
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
fi
echo "Killing any previously running instances..."
./kill-all.sh
echo "Starting new instance..."
./run.sh & disown
