#!/bin/bash

# Start the logger
setsid ./logger.sh & disown

# Start the killer helper
setsid ./pgid_killer.sh & disown

# Start cache cleanup script
setsid ./cleanup-cache.sh & disown

# Repair permissions
setsid ./repair-permissions.sh & disown

# Monitor
setsid ./monitor.sh & disown

# Start the webserver
setsid ./restart.sh & disown

setsid bash -c "sleep $((4 * 3600)) ; /sbin/reboot" & disown
