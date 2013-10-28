##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic  main.cpp && ./a.out
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic main.cpp -S && cat main.s
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic main.cpp -fdump-tree-original && cat main.cpp.003t.original
clang++  -std=c++11 -O3 -W -Wall -Wextra -pedantic  main.cpp && ./a.out && c++filt -t d
##gcc-4.6 -x c -std=c99 -W -Wall -Wextra -pedantic -Os main.cpp && ./a.out
##clang -x c -std=c99  -W -Wall -Wextra -pedantic -Os main.cpp && ./a.out