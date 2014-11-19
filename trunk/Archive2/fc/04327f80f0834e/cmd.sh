clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ 
echo ------ && ./a.out
echo ------ && ./a.out -e one two buckle my shoe
echo ------ && ./a.out -d three four open the door
echo ------ && ./a.out -x five six pick up sticks