ln -s /Archive2/9c/1da956b7153813/main.cpp reverse.cpp
clang++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors -oreverse reverse.cpp
clang++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors -oucase main.cpp
cat main.cpp | ./reverse | ./ucase