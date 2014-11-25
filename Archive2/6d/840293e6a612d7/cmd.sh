set -x; 
g++ -std=c++1y -O3 -Wall -pedantic -pthread main.cpp -o a.out && ./a.out
clang++ -std=c++1y -O3 -Wall -pedantic -pthread main.cpp -o a.out && ./a.out
clang++ -stdlib=libc++ -O3 -std=c++1y -Wall -pedantic -pthread main.cpp -o a.out && ./a.out