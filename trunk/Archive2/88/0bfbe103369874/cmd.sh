g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && touch "file_test.dat" && \
echo "16 99.2 89.1 John Pimentel" < file_test.dat && ./a.out