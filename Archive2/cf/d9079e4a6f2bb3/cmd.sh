##set -x ; g++ -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O0  -pedantic  -pthread main.cpp && ./a.out
##set -x ; clang++ -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O0  -pedantic -Wall -pthread main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -pedantic main.cpp && ./a.out
set -x ; clang -x c -std=c99 -Wall -Wextra -O0  -pedantic main.cpp && ./a.out