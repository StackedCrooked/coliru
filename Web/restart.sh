#!/bin/bash
exec > >(logger -t $0) 2>&1
./killuid.sh 2001
./killuid.sh 2002
./run.sh & disown
