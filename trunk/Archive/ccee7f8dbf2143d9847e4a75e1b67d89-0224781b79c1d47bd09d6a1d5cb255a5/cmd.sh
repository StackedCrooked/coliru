g++ -std=c++11 -O2 -pthread main.cpp && ./a.out ; function print() { echo "$1: " && cat $1 ; } ; print 'foo.hpp' ; print 'foo.cpp' ; print 'test.cpp' ; g++ foo.cpp test.cpp -o app && ./app