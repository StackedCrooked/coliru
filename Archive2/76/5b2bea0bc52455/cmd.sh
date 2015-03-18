ln -s main.cpp main.c && clang -std=c99 -O3 -Wall -Wextra -pedantic-errors main.c && ./a.out <<< '123 45 6 78'
#clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && ./a.out
#echo ============== && sleep 2 && g++ -std=c++14  -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && ./a.out