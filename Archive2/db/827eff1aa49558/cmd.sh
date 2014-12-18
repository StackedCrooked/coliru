clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic main.cpp && ./a.out >libc++
g++ -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out  >stdlibc++
diff -y -t stdlibc++ libc++