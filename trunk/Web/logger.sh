#!/bin/bash

cd "$(dirname $0)"
rm -f stdout ; mkfifo stdout ; chown webserver:coliru stdout
rm -f stderr ; mkfifo stderr ; chown webserver:coliru stderr

{ while true ; do while read line ; do logger "stdout: $line" ; done <stdout ; logger "Broke out of stdout loop" ; sleep 10 ; done } & disown
{ while true ; do while read line ; do logger "stderr: $line" ; done <stderr ; logger "Broke out of stderr loop" ; sleep 10 ; done } & disown
