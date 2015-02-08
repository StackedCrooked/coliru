#clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo ok && g++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors main.cpp -lboost_regex && ./a.out