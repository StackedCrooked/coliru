clang++ -std=c++11 -stdlib=libc++ -pedantic main.cpp -lsupc++ -o test && ./test
gcc -std=c++11 -pedantic -lstdc++ main.cpp -o test && ./test