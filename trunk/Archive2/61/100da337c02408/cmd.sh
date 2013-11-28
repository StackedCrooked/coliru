echo "Using c++03:"
g++-4.8 -O2 -Wall -pedantic -pthread main.cpp && ./a.out

echo "Using c++11:"
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out