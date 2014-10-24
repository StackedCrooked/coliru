g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -o rle
echo abc | ./rle
echo aaabbbccc | ./rle