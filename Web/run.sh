#!/bin/bash
if [ "$(whoami)" != "webserver" ]; then
	echo "For security reasons this script must be run by a user named \"webserver\"."
	exit 1
fi
ruby webserver.rb stacked-crooked.com 80
