set -x ;
g++-4.9 -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -fno-elide-constructors main.cpp && ./a.out
clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion -fno-elide-constructors -stdlib=libc++ main.cpp -lsupc++ && ./a.out
# clang++ -std=c++1y -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out