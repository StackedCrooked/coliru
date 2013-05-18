#!/bin/bash
[ "$#" == "1" ] || {  echo "Usage: $(basename $0) user_id" 1>&2 ; exit 1 ; }
ps -eopgid,uid | grep $1 | head -n1 | awk '{print $1}' | xargs -I {}  kill -9 -{}
