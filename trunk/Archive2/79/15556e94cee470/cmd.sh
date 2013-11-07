set -x ; clang++ -Os -std=c++11 -Wall -pedantic main.cpp  && (
    dd if=/dev/urandom count=32 bs=1 2>/dev/null > input.dat;
    ./a.out; echo 'And `od` output:'; 
    od -w8 -A none -t f8 -v /tmp/input.dat;
)