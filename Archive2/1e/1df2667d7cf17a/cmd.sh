ln -s /Archive2/4e/15a6cbcbf5852d/main.cpp test.cpp
g++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors -ofilt main.cpp
echo . && echo . && g++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors -c -fdiagnostics-show-location=once -fno-diagnostics-show-caret -fno-diagnostics-show-option test.cpp 2>&1 | ./filt