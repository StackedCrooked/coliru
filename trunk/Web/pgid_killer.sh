#!/bin/bash
set -x
rm -f .pgid_killer
mkfifo .pgid_killer
chmod a+w .pgid_killer
while true ; do read line <.pgid_killer ; kill -9 "$line"  ; done 
