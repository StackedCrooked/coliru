clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo -e '\nclang++/libc++ compiled without errors\n'
g++-4.9 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo -e '\ng++/libstdc++ compiled without errors\n'
clang++ -std=c++11 -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo -e '\nclang++/libstdc++ compiled without errors\n'