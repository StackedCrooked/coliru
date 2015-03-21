set -x;
g++  -S  -O0 -std=c++11 main.cpp
c++filt < main.s > temp.s
cat temp.s