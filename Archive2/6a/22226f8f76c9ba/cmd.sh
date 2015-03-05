cat <<INPUT >5.txt; g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
t # 0
v 0 0
v 1 3
v 2 9
e 2 1 68
e 0 1 10
e 0 2 4
t # 1
v 0 2
v 1 11
v 2 6
v 3 10
v 4 18
v 5 14
e 0 1 15
e 2 5 19
e 1 3 20
t # 2
v 0 6
v 1 11
e 0 1 13
t # 3
v 0 2
v 1 11
v 2 19
v 3 2
e 0 1 15
e 1 2 11
e 0 3 19
t # 4
v 0 1
v 1 16
v 2 14
e 0 1 8
e 1 2 5
e 0 2 19
INPUT