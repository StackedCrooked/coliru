clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ -o my_wc
cat main.cpp | wc
cat main.cpp | ./my_wc