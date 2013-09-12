echo $(($(date +%s) - $(stat -L --format %Y $1)))
