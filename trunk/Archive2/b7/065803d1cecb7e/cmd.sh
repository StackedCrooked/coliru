set -x;
g++-4.9 -std=c++1y -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter /Archive2/bb/d82001fa573011/main.cpp && ./a.out
# g++-4.9 -std=c++1y -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out
# clang++ -std=c++1y -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++ main.cpp -lsupc++ && ./a.out