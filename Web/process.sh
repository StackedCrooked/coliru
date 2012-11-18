#!/bin/bash
#set -x
set -e 
ulimit -t 5


(file request.txt 2>/dev/null 1>&2) || { echo "No request file found. Exiting." >&2 ; exit 1 ; }

{ { sleep 3 && echo "Timeout" 1>&2 ; /bin/bash -c 'killall test' ; } & }
{ trap "kill $!" INT ERR EXIT && { sudo -u sandbox ./sandbox.sh ./request.txt ; } || { echo "Compilation was terminated before it could finish." 1>&2  ; } ; }
exit 0
