set -x ;
g++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -fno-elide-constructors main.cpp && ./a.out
# clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -stdlib=libc++ main.cpp -lsupc++ && ./a.out