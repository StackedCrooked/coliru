g++-4.8 -std=c++11 -O2 -Wall -pedantic main.cpp -lboost_iostreams -lboost_system
LANG=C od -f -A none --width=12 /dev/urandom | head -n 100 > input.txt
./a.out