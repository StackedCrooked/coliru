#!/bin/bash
source coliru_env.source
source logger.source

sudo -u webserver -E ruby webserver-sinatra.rb -o "${COLIRU_URL}"
echo "WEBSERVER EXITED WITH CODE $?"
