#!/bin/sh
./timeout 5 nice -n 10 systrace -a -t -d . -e ./compile-and-run.sh
