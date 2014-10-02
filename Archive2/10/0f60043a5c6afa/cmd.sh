ln -s /Archive2/2a/e55334978bb511/main.cpp module_a.cpp
ln -s /Archive2/7f/fa4e716e43e587/main.cpp module_b.cpp
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp module_a.cpp module_b.cpp && ./a.out