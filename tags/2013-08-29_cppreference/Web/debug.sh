#!/bin/bash
source coliru_env.source
shotgun webserver-sinatra.rb -p 8080 -o $(ifconfig eth0 | grep 'inet addr' | perl -p -e 's,\s+inet addr:([0-9.]+).*,\1,')
