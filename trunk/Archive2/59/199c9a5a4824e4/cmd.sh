##ls -lart /usr/share/local
set -x ; clang++ -std=c++11 -O3 -W -Wall -Wconversion  -pedantic-errors -pedantic -Werror=uninitialized -pthread main.cpp  &&  ./a.out
##set -x ; g++ -std=c++11 -O0 -W -Wall -Wextra -Wconversion -Werror=uninitialized -pedantic -pthread main.cpp  && ./a.out
##set -x ; g++ -std=c++11 -O2 -W -Wall  -Wconversion -pedantic -pthread main.cpp -S  && cat main.s
##set -x ; gcc -x c -std=c99 -O3  -fno-builtin -W -Wall -Wconversion  -Wextra -pedantic  -pthread main.cpp  && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -fno-builtin -W -Wall -Wextra -pedantic  -pthread -S main.cpp  && cat main.s
##set -x ; clang -x c -std=c99 -O1 -W -Wall -pedantic -Weverything -Wconversion -pthread main.cpp  && ./a.out
##set -x ; clang -x c -std=c99 -O0 -W -Wall -pedantic  -pthread main.cpp -S  && cat main.s