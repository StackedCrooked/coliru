set +x ; g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -o uriencode
echo 'http://en.wikipedia.org/wiki/Percent-encoding' | ./uriencode