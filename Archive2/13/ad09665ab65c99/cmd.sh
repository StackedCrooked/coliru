g++-4.8 -std=c++11 -O0 -Wall -pedantic -pthread main.cpp -DLOOP_A -o a && \
g++-4.8 -std=c++11 -O0 -Wall -pedantic -pthread main.cpp -DLOOP_B -o b && \
time ./a && time ./b