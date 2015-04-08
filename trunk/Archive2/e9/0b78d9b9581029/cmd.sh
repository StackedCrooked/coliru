cat > input.txt <<INPUT
one=two
three=four

# Comment
five=six
INPUT
clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp && ./a.out