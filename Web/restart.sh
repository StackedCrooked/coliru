#!/bin/bash
bash -c "exec > >(logger -t $0) 2>&1 ; ./killuid.sh 2001 ; ./killuid.sh 2002 ; while true ; do ./run.sh ; done" & disown
