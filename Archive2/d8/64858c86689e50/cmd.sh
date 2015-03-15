cat <<INPUT >testgUe.txt; ulimit -v $((1024*512)); g++ -m32 -std=c++11 -Os -pedantic main.cpp && ./a.out
t # 0
v 0 5
v 1 9
v 2 8
v 3 7
e 0 1 4
e 1 2 68
e 3 2 18
INPUT