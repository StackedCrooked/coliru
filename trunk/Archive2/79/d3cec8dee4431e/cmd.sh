##clang++ --version
##g++ --version
##set -x ; g++-4.9 -std=c++1y -Wall -Wextra -Wconversion -pedantic -O3 -pthread main.cpp && ./a.out
##g++ --version
##set -x ; g++-4.9 -std=c++11 -Wall  -Wextra -Wconversion -pedantic  -O3  -pedantic  -pthread -S main.cpp && cat main.s
set -x ; clang++ -std=c++1y  -fsanitize=undefined -Wall -Wextra -Wconversion  -pedantic -O0  -pthread main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0  -W -Wall -Wextra -pedantic -Wconversion  main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -S main.cpp && cat main.s | grep log
##set -x ; clang -x c -std=c99 -fsanitize=undefined -Wall -Wextra -Wconversion -Weverything  -O0  -pedantic main.cpp && ./a.out