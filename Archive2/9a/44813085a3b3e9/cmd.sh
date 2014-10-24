g++ -std=c++11 -O2 -Wall -Wextra -Werror -pedantic -pthread main.cpp -o uriencode
s='%' ; for i in {1..20} ; do s="$(echo "$s" | ./uriencode)" ; echo "$i $s" ; done