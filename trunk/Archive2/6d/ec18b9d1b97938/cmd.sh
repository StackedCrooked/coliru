g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors -O2 -pthread main.cpp -lpthread 
echo -e '\n1' && ./a.out
echo -e '\n2' && ./a.out just_not_there.txt 
echo -e '\n3' && ./a.out main.cpp