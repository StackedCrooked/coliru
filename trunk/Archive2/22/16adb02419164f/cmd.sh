#clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
/usr/bin/head -n -10 main.cpp > /tmp/tmp.cpp && mv /tmp/tmp.cpp main.cpp && cat main.cpp
which head