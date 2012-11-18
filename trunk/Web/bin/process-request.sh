set -x
set -e 
if [[ ! -f request.txt ]] ; then
    echo "No request file found. Exiting." 2>&1 && exit 1
fi

{ { sleep 5 && echo "Timeout" 1>&2 ; } & } && { trap "kill $!" INT ERR EXIT && sudo -u sandboxer bin/process-request-sandboxed.sh request.txt && echo "Done!" ; }
