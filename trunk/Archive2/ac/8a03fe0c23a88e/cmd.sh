echo -e '------- clang++ -------\n' && clang++ -std=c++11 -O3 -march=native -Wall -Wextra -pedantic-errors -fomit-frame-pointer -c -S main.cpp && cat main.s
echo -e '\n-----  g++ ------\n' && g++ -std=c++11 -O3 -march=native -Wall -Wextra -pedantic-errors -fomit-frame-pointer -c -S main.cpp && cat main.s