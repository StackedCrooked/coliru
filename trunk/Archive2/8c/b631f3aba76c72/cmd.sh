set -x;
g++-4.9 -std=c++1y -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread -DDOESNT_EXIST main.cpp && ./a.out
g++-4.9 -std=c++1y -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp && ./a.out
# clang++ -std=c++1y -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++ -pthread -DDOESNT_EXIST main.cpp -lsupc++ && ./a.out