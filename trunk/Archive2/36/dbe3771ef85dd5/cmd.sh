set -x ;
g++-4.9 -std=c++03 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter main.cpp -pthread -lboost_system -lboost_thread && ./a.out
# clang++ -std=c++14 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -stdlib=libc++ main.cpp -lsupc++&& ./a.out
# clang++ -std=c++14 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out