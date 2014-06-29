set -x ;
clang++ -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out
# g++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out