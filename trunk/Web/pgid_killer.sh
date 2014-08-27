#!/bin/bash

# Started as /root/coliru/Web/pgid_killer.sh
cd "$(dirname $0)"

[ -p .pgid_killer ] || mkfifo .pgid_killer 
chmod a+w .pgid_killer

while true ; do
    ./_pgid_killer.sh
    sleep 10
done
