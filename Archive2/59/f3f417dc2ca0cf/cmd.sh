set -x
clang++ -O2 -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out; echo $?
g++ -O2 -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out; echo $?