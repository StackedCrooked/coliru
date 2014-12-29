set -x;
(clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp 2>&1 && ./a.out 2>&1) > a;
(clang++ -DFIXED -std=c++11 -O2 -Wall -pedantic -pthread main.cpp 2>&1 && ./a.out 2>&1) > b;
diff -y -W250 a b;