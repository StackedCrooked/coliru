clang++ --version
##g++-4.8 --version
##set -x ; g++-4.9 -std=c++1y -Wall -Wextra -Wconversion -pedantic -O3 -pthread  main.cpp && ./a.out 
##g++ --version
##set -x ; g++-4.9 -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O3  -pedantic  -pthread -S main.cpp && cat main.s 
set -x ; clang++ -std=c++11 -fsanitize=undefined,signed-integer-overflow -Wall -Wextra -Wconversion  -pedantic -O0  -Wall -pthread  main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -Wall -Wconversion main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -S main.cpp && cat main.s | grep 15
##set -x ; clang -x c -std=c99 -fsanitize=undefined  -Wall -Wextra -Wconversion -O0  -pedantic main.cpp && ./a.out