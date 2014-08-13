echo '*** clang++ ***' && clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ -o test && ./test && echo ok
echo '*** g++-4.9 ***' && g++-4.9 -std=c++11 -Wall -Wextra -pedantic-errors main.cpp -o test && ./test && echo ok
echo '*** g++-4.8 ***' && g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors main.cpp -o test && ./test && echo ok