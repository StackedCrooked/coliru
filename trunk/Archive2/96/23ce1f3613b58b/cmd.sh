#clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic-errors main.cpp -lsupc++ && ./a.out
echo '----------- gnu + boost -------------------------'
g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors main.cpp -lboost_regex && ./a.out