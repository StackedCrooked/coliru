g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic    main.cpp && ./a.out
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic  -O2 main.cpp -S  && cat main.s
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic -fno-builtin main.cpp -S && cat main.s
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic main.cpp -fdump-tree-original && cat main.cpp.003t.original
##clang++  -std=c++11 -O3 -W -Wall -Wextra -Weverything -pedantic   main.cpp && ./a.out
##c++filt -t d
##gcc -x c -std=c99 -W -Wall -Wextra -Wconversion -pedantic -fno-builtin -O2 main.cpp -pthread -lm && ./a.out
##gcc -x c -std=c99 -W -Wall -Wextra -Wconversion -pedantic -fno-builtin -O0 -S main.cpp -pthread -lm && cat main.s
##clang -x c -std=c99  -W -Wall -Wextra -Weverything -pedantic -Os main.cpp && ./a.out