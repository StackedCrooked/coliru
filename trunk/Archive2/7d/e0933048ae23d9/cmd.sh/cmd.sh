##g++ -std=c++11 -O3 -Wall -Wextra -Wconversion -pedantic -Werror=return-type -pthread main.cpp && ./a.out
##clang++ -std=c++11 -O3 -Wall -Wextra -Wconversion -pedantic -Werror=return-type -pthread main.cpp && ./a.out
##gcc -x c -std=c99 -O0 -Wall -Wextra -Wconversion -pedantic -pthread main.cpp && ./a.out
clang -x c -std=c99 -O2 -Wall -Wextra -Wconversion -pedantic -pthread main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -pedantic  -pthread main.cpp -fverbose-asm -S  && cat main.s