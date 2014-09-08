#!/bin/bash

# Start cache cleanup script
nohup ./cleanup-cache.sh >/dev/null 2>&1 </dev/null & disown

# Repair permissions
nohup ./repair-permissions.sh >/dev/null 2>&1 </dev/null & disown

# Start the webserver
nohup ./restart.sh >/dev/null 2>&1 </dev/null & disown


#nohup bash -c "sleep $((4 * 3600)) ; /sbin/reboot" >/dev/null 2>&1 </dev/null & disown
