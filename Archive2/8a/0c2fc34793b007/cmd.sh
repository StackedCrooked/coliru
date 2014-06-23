echo '-------- clang++ -----------'

clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo 'compiled without errors'
echo -e '\n\n---------- g++ -------------\n'
g++-4.9 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo 'compiled without errors'