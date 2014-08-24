#!/bin/bash

# Script checks if webserver is still running
log() {
    echo "$(basename $0): $*"
    logger "$(basename $0): $*"
}

num_restarts=0
while true ; do
    num="$(ps -eouid,comm,args | sed -e 's,^ *,,' | grep '^2001' | grep ruby | wc -l | awk '{print $1}')"
    log "There are $num webserver processes running. num_restarts=${num_restarts}."

    [ "$num_restarts" -ge 10 ] && {
        reboot_delay=60
        log "Restarted $num_restarts times. Rebooting after $reboot_delay seconds."
        sleep $reboot_delay # delay prevents nasty reboot loop
        reboot
    }

    [ "$num" == "0" ] && {
        log "Restarting."
        ./restart.sh
        let num_restarts++
    }
    sleep 10
done
