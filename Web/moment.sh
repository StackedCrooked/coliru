#!/bin/bash
[ $# -eq 1 ] || { echo "Usage: $0 DurationInSeconds" 1>&2 && exit 1 ; }
m=60
H=3600
D=$((24 * $H))
W=$((7 * $D))
[ $1 -le $m ] && echo "$1 seconds" && exit 
[ $1 -le $H ] && echo "$(($1/$m)) minutes" && exit 
[ $1 -le $D ] && echo "$(($1/$H)) hours" && exit 
[ $1 -le $W ] && echo "$(($1/$H)) hours" && exit 
echo "$(($1/$D)) days" && exit 
