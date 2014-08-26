#!/bin/bash

# Start the logger
nohup ./logger.sh &

# Start the killer helper
nohup ./pgid_killer.sh &

# Start cache cleanup script
nohup ./cleanup-cache.sh &

# Repair permissions
nohup ./repair-permissions.sh &

# Monitor
nohup ./monitor.sh &

# Start the webserver
nohup ./restart.sh &

nohup bash -c "sleep $((4 * 3600)) ; /sbin/reboot" &
