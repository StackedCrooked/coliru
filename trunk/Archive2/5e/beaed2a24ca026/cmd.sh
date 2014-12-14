cat>input.txt<<INPUT; clang++ -std=c++11 -Os -Wall main.cpp && ./a.out <<< "input.txt A C"
Vertices:
A,B,C,D,E
Edges:
(A, B, 3)
(B, C, 4)
(C, D, 5)
(A, E, 6)
(C, E, 2)
INPUT