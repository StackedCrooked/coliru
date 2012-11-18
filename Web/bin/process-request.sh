#!/bin/bash
set +x
set -e 
(file request.txt 2>/dev/null 1>&2) || { echo "No request file found. Exiting." >&2 ; exit 1 ; }

{ { sleep 3 && echo "Timeout" 1>&2 ; /bin/bash -c 'killall test' ; } & }
{ trap "kill $!" INT ERR EXIT && { sudo -u sandboxer bin/process-request-sandboxed.sh ./request.txt ; } ; }
exit 0
