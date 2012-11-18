#!/bin/bash
set +x
set -e 
#type ./request.txt &>/dev/null || { echo "No request file found. Exiting." >&2 ; exit 1 ; }

{ { sleep 3 && echo "Timeout" 1>&2 && /bin/bash -c 'killall test' ; exit 1 ; } & }
PID=$!
sudo -u sandboxer bin/process-request-sandboxed.sh ./request.txt
kill -9 $PID
exit 0
