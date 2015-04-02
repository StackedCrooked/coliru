set -x
clang++ -O2 -stdlib=libc++ -std=c++11 -Weverything -Wparentheses -Wextra main.cpp -lcxxrt -ldl && ./a.out && g++ -O2 -std=c++11 -Wall -Wextra main.cpp -lcxxrt -ldl && ./a.out