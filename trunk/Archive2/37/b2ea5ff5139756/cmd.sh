##clang++ --version
##g++-4.8 --version2set -x ;
##g++-4.8 -std=c++11   -Wall -Wextra -Wconversion -pedantic  -O3 -pthread  main.cpp && ./a.out 
##g++ --version
##set -x ; g++-4.9 -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O3  -pedantic  -pthread -S main.cpp && cat main.cpp 
##set -x ; clang++  -std=c++14  -fsanitize=undefined,signed-integer-overflow  -O3 -Wall -Wextra -Wconversion  -pedantic -Wall -pthread  main.cpp && ./a.out goog
set -x ; gcc -x c -std=c99 -pedantic-errors main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -S main.cpp && cat main.s 
##set -x ; clang -x c  -fsanitize=undefined   -Wall -Wextra -Wconversion -O3  -pedantic-errors  main.cpp && ./a.out