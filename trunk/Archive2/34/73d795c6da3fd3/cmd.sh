set -x;
g++ -g -std=c++1y -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -fno-elide-constructors main.cpp && ./a.out
clang++ -g -std=c++1y -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++ -fno-elide-constructors main.cpp -lsupc++ && ./a.out