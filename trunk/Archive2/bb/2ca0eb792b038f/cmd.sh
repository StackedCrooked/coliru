set -x
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic main.cpp ; echo "$?"
g++ -std=c++11 -O2 -Wall -pedantic main.cpp ; echo "$?"