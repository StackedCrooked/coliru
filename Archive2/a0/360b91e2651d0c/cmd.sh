##g++ --version
##set -x ; g++-4.8 -std=c++03 -Wall -Wextra -Wconversion -pedantic  -O0  -pedantic  -pthread main.cpp && ./a.out
##g++ --version
##set -x ; g++ -std=c++03 -Wall -Wextra -Wconversion -pedantic  -O0  -pedantic  -pthread -S main.cpp && cat main.s
##set -x ; clang++ -std=c++11  -fsanitize=undefined -Wall -Wextra -Wconversion  -pedantic  -O3  -Wall -pthread main.cpp && ./a.out
##set -x ; gcc -x c -std=c90 -O0 -W -Wall -Wextra -Wconversion -pedantic main.cpp && ./a.out
set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -fverbose-asm -S main.cpp && cat main.s
##set -x ; clang -x c -std=c99 -Wall -Wextra -O0 -Wconversion -Weverything -pedantic main.cpp && ./a.out