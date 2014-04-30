##g++ --version
##clang++ --version
clang++  -std=c++11 -fsanitize=undefined -fsanitize=unreachable -O0  -W -Wall -Wextra  -Wconversion -pedantic   main.cpp && ./a.out
##g++ --version
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic      main.cpp && ./a.out
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic  -O2 main.cpp -S  && cat main.s
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic -fno-builtin main.cpp -S && cat main.s
##g++ -std=c++11 -O0 -W -Wall -Wextra -pedantic main.cpp -fdump-tree-original && cat main.cpp.003t.original
##c++filt -t d
##gcc -x c -std=c99 -W -Wall -O0 -fno-builtin  -Winit-self  main.cpp -pthread -lm && ./a.out
##gcc -x c -std=c99  -Wuninitialized -Winit-self  main.cpp -pthread -lm && ./a.out
##gcc -x c  -fstrict-aliasing -O3 -Wstrict-aliasing -std=c99  main.cpp && echo "100" | ./a.out
##gcc -x c -std=c99 -W -Wall -Wextra -Wconversion -pedantic -fno-builtin -O0 -fverbose-asm  -S main.cpp -pthread -lm && cat main.s | grep offsetArray
##gcc -x c -std=c99 -O0 -fverbose-asm  -S main.cpp && cat main.s 
##clang -x c -std=c99 -fsanitize=undefined  -W -Wall -Wextra -Weverything -Wconversion -pedantic  -O0 main.cpp -lgmp && ./a.out
##clang -x c -std=c99 -Wall -O0 main.cpp && ./a.out
##gcc -x c -std=c99  -W -Wall -Wextra  -pedantic -E main.cpp