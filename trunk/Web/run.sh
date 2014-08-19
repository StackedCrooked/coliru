#!/bin/bash
source coliru_env.source

# delegate to calller
#source logger.source

setsid sudo -u webserver -E ruby webserver-sinatra.rb -o ${COLIRU_URL}
