set -x ;
g++-4.8 -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out
g++-4.9 -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out
# clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -stdlib=libc++ main.cpp -lsupc++ && ./a.out
# clang++ -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out