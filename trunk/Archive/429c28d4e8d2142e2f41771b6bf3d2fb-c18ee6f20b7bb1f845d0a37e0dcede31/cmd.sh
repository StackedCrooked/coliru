echo 'compiling...'
time g++ -std=c++11 -O2 -Wall -Wextra -Werror -pedantic-errors -ftemplate-depth=10000 main.cpp -ltbb
echo 'running...'
time ./a.out