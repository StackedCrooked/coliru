#!/bin/bash
if [ "$(whoami)" != "webserver" ]; then
	echo "For security reasons this script must be run by a user named \"webserver\"."
	exit 1
fi
ruby webserver.rb "10.0.2.15" 8080
