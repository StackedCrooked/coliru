echo "g++ ...:"
g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out

echo 
echo "g++ -DADD_MAKE_UNIQUE ...:"
g++-4.8 -DADD_MAKE_UNIQUE -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out