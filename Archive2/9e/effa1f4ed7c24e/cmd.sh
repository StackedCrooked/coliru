set -x ; clang++ -std=c++11 -O2 -W -Wall -Weverything  -Wconversion -pedantic  -pthread main.cpp  && ./a.out
##set -x ; g++-4.6 -std=c++0x -O2 -W -Wall  -Wconversion  -pedantic -pthread main.cpp  && ./a.out
##set -x ; gcc -x c -std=c99 -O2 -W -Wall -Wextra -pedantic  -pthread main.cpp  && ./a.out
##set -x ; clang -x c -std=c99 -O2 -W -Wall -Wextra -pedantic  -pthread main.cpp  && ./a.out