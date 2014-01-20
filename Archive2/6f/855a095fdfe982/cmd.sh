clang++ -DCOUNT=2 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out && wc -l pids
rm pids
clang++ -DCOUNT=3 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp && ./a.out && wc -l pids