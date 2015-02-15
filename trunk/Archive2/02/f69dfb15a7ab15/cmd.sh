mv main.cpp code &&
cat code | perl -ne 'print if $. < 10' > main.ll &&
cat code | perl -ne 'print if $. > 10' > main.cpp &&
clang++ main.{ll,cpp} -std=c++14 -Wall -Wextra -Werror -pedantic -O2 &&
./a.out