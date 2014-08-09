#!/bin/bash

debug="${debug:-no}"
echo "debug=$debug"


get_sandbox_pids() {
    ps -eopid,args | grep 'sandbox\.sh' | grep -v grep | awk '{print $1}' | uniq
}


# Checks for sandbox processes that have a lifetime that is too long
# while true ; do 
#     get_sandbox_pids | while read line ; do
#         [ ! -f "$line" ] && {
#             echo "We got a new pid: $line"
#             echo "$(date +%s)" >$line
#         } || { 
#             elapsed="$(($(date +%s) - $(cat "$line")))"
#             echo "$line has been active for $elapsed seconds"
#             [ "$elapsed" -gt "60" ] && {
#                 echo "Killing $line"
#                 kill -9 "$line"
#             }
#         }
#     done
#     sleep 5
# done  & disown

run() {
    while true ; do
        sandbox_pids="$(get_sandbox_pids)"
        num_sandboxes="$(echo "$sandbox_pids" | wc -l)"
        while [ "$num_sandboxes" -gt "2" ] ; do 
            echo "There are $num_sandboxes sandbox processes. Kill the oldest."
            pid_to_kill="$(echo "$sandbox_pids" | head -n1)"
            [ "$pid_to_kill" == "" ] && break
            echo "Killing $pid_to_kill"
            kill -9 "$pid_to_kill"
            sandbox_pids="$(get_sandbox_pids)"
            num_sandboxes="$(echo "$sandbox_pids" | wc -l)"
        done

        # Count number of defunct processes
        count="$(ps -ef | grep 'sandbox\|2002\|2001' | wc -l)"
        if [ $count -gt 100 ] ; then
            echo "There are $count processes. This is suspiciously high. I will reboot the webserver in 5 minutes."
            { sleep 300 ; reboot ; } & disown
        fi
        sleep 10
    done
}


[ "$debug" == "no" ] && {
    echo "Redirect output to the logger."
    echo "run and disown"
    source logger.source
    run & disown
} || {
    echo "just run"
    run
}

