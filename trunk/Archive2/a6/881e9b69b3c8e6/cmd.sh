clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp && ./a.out <<HERE
fanout_n #(2, 0, 0) FANOUT_2 (c7552_wire_2, {c7552_wire_2_0, c7552_wire_2_1});
something else;
fanout_n #(2, 0, 0) FANOUT_2 ({c7552_wire_2}, {c7552_wire_2_0, c7552_wire_2_1});
HERE