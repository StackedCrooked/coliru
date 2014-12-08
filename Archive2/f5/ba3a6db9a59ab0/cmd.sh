g++ -std=c++11 -Wall -Wextra -pedantic -fexceptions main.cpp && ./a.out
g++ -std=c++11 -Wall -Wextra -pedantic -fno-exceptions main.cpp && ./a.out
clang++ -std=c++11 -Wall -Wextra -pedantic -fexceptions main.cpp && ./a.out
clang++ -std=c++11 -Wall -Wextra -pedantic -fno-exceptions main.cpp && ./a.out