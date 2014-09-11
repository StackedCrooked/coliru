set -x
clang++ -O2 -stdlib=libc++ -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out sum 1.0 2.0 3.0; echo $?
g++ -O2 -std=c++11 -Wall -Wextra -pedantic main.cpp && ./a.out sum 1.0 2.0 3.0; echo $?