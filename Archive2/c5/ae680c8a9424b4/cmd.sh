mv main.cpp code &&
cat code | perl -ne 'print if $. < 10' > math.ll &&
cat code | perl -ne 'print if $. > 10' > main.cpp &&
clang++ -std=c++14 -Wall -Wextra -Werror -pedantic -O2 -flto math.ll main.cpp &&
objdump -d a.out