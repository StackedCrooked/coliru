##clang -x c -std=c99 -O3 -W -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
##clang -x c  -O3 -W -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
gcc -x c -std=c99 -O3 -W -Wall -Wextra -pedantic -pthread main.cpp && ./a.out && objdump -s -j .rodata a.out
##g++-4.8 -std=c++11 -O2 -W -Wall -Wextra  -Wconversion -pedantic -pthread main.cpp && ./a.out