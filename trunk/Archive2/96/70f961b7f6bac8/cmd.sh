echo "" && echo "Using 16 parameters..." && clang++ -std=c++11 -W{all,extra,no-unused-parameter} -pedantic-errors main.cpp && ./a.out
echo "" && echo "Using 17 parameters..." && clang++ -std=c++11 -W{all,extra,no-unused-parameter} -pedantic-errors main.cpp -DUSE_17_PARAMS && ./a.out