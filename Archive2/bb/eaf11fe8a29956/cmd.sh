echo -e 'stdout\n------'
clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && ./a.out
echo -e '\nfile /tmp/half_of_jabberwocky\n-------------------------------'
cat /tmp/half_of_jabberwocky