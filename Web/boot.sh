#!/bin/bash

# Start the logger
./logger.sh & disown

# Start the killer helper
./pgid_killer.sh & disown

# Start cache cleanup script
./cleanup-cache.sh & disown

# Repair permissions
./repair-permissions.sh & disown

# Start the webserver
./restart.sh & disown

{ sleep 3600 ; /sbin/reboot ; } & disown

