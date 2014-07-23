#!/bin/bash
# This script declares a global persistent variable and sets the value 1.
# Every time the script is re-run the variable is incremented.
# Example:
#   fvar_inc a => 1
#   fvar_inc a => 2
#   reboot # wait a while
#   fvar_inc a => 3 
[ "$#" == "1" ] || {
    echo "Usage: $(basename $0) filename" 1>&2
    exit 1
}

mkdir -p "$HOME/.fvars" 
export file="$HOME/.fvars/${1}"
echo "$(($(cat "$file" 2>/dev/null || echo 0) + 1))" > $file
cat $file
