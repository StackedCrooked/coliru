echo -e '\n------------------------------------------------------------------------------\n'
g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
echo -e '\n----------------------   TRY_BYPASS_SETTER    ---------------------------------\n'
g++-4.8 -DTRY_BYPASS_SETTER -std=c++11 -Wall -Wextra -pedantic-errors main.cpp && ./a.out