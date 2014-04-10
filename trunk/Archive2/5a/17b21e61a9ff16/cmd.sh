gcc -x c -std=c99  -Wuninitialized -Winit-self  main.cpp -pthread -lm && ./a.out
##gcc -x c -std=c99  -Wall -Winit-self  main.cpp -pthread -lm && ./a.out
##clang -x c -std=c99  -Wall main.cpp -pthread -lm && ./a.out