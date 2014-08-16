g++-4.9 -std=c++1y -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo ok
clang++ -std=c++1y -stdlib=libstdc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo ok