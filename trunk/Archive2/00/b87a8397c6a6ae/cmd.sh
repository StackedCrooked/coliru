set -x ; g++ -std=c++11 -W -Wall -Wextra -Wconversion -pedantic  -O2 -S main.cpp  && cat main.s
##set -x ; g++ -std=c++11 -W -Wall -Wextra -Wconversion -pedantic  -O2  main.cpp  && ./a.out