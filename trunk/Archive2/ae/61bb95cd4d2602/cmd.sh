##g++ --version
##set -x ; g++-4.8 -std=c++03 -Wall -Wextra -Wconversion -pedantic  -O0  -pedantic  -pthread main.cpp && ./a.out
##g++ --version
##set -x ; g++ -std=c++03 -Wall -Wextra -Wconversion -pedantic  -O0  -pedantic  -pthread -S main.cpp && cat main.s
##set -x ; clang++ -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O3  -Wall -pthread main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -S main.cpp && cat main.s
set -x ; clang -x c -std=c99 -Wall -Wextra -O0  -pedantic main.cpp && ./a.out