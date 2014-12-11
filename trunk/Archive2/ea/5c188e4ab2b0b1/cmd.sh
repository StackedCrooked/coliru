set -x; g++ -std=c++1y -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out; echo $?
clang++ -std=c++1y  -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out; echo $?
# clang++ -stdlib=libc++ -std=c++1y -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out; echo $?