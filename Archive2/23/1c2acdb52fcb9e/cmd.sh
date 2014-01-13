gcc -x c -std=c99 -Wc++-compat -W -Wall -Wextra -Wconversion -pedantic -fno-builtin -O3 main.cpp -pthread -lm && ./a.out
##clang++  -std=c++11 -O0  -W -Wall -Wextra -Wconversion -pedantic   main.cpp && ./a.out
##g++ -std=c++11  -O0 -W -Wall -Wextra -Wconversion -pedantic    main.cpp && ./a.out