g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp ; printf "\n\n"
./a.out | perl -pe 's,void print_type.*? = (.*?)\],\1,g'