set -x ; gcc -x c -std=c99 -O0 -Wall -pedantic -pthread -S main.cpp && cat main.s