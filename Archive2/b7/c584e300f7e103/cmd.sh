echo ' **** not taking its address, and not defining it ****'
g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo
echo ' **** taking its address, but not defining it ****'
g++-4.8 -DTAKE_ITS_ADDRESS -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo
echo '**** taking its address, and also defining it ****'
g++-4.8 -DTAKE_ITS_ADDRESS -DDEFINE_IT -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out