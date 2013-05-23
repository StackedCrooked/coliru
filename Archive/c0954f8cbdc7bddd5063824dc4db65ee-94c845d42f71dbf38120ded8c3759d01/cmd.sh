echo 'compiling...'
time g++ -std=c++11 -O2 -Wall -Wextra -Werror -pedantic-errors main.cpp -ltbb
echo 'running...'
time ./a.out
echo 'done!'