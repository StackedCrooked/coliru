#!/bin/bash
[ $# -eq 2 ] || echo "Usage: $(basename $0) action service_name"

start() {
    echo "Started action $0"
}

stop() {
    echo "Started action $0"
}

type $1 >/dev/null 2>&1 || {
    echo "Unsupported action: $1" 1>&2
    exit 1
}   

$1 $2