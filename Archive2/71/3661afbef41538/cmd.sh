##gcc -x c -std=c99  -W -Wall  -Wextra  -pedantic  -O0 -fno-builtin  main.cpp -pthread -lm && ./a.out
g++-4.8 -std=c++11  -O0 -Wall -Wextra -Wconversion  -pedantic  -pthread -pedantic-errors -fno-builtin main.cpp  && ./a.out
##g++-4.8 -std=c++11  -O0 -Wall -Wextra -Wconversion -S -pedantic  -pthread -pedantic main.cpp  && cat main.s