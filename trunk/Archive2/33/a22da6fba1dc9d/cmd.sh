clang++ --version && clang++ -std=c++11 -stdlib=libc++ -pedantic main.cpp -lsupc++ -o test && ./test
gcc --version && gcc -std=c++11 -pedantic main.cpp -o test && ./test