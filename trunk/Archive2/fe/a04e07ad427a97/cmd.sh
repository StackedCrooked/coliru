##clang++ --version
##g++-4.8 --version2
set -x ;g++-4.9 -std=c++11   -Wall -Wextra -Wconversion -Wnarrowing -Wundef -pedantic-errors  -O3 -pthread  main.cpp && ./a.out 
##g++ --version
##set -x ; g++-4.9 -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O3  -pedantic  -pthread -S main.cpp && cat main.cpp 
##set -x ; clang++  -std=c++11 -fsanitize=undefined,signed-integer-overflow  -O3 -Wall -Wextra -Wconversion -pedantic -Wall -pthread  main.cpp && ./a.out 
##set -x ; gcc -x c -std=c99 -O3  -Wall -Wconversion -pedantic main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -S main.cpp && cat main.s 
##set -x ; clang -x c  -fsanitize=undefined   -Wall -Wextra -Wconversion -O3  -pedantic  main.cpp && ./a.out