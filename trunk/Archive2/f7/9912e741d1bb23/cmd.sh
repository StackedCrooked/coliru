set -x 
g++-4.8 -std=c++1y -O3 -S main.cpp -masm=intel && cat main.s