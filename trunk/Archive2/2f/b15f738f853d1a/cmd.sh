echo '<html><body><pre>'
f() { g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out ; }
declare -f f ; f
echo '</html></body></pre>'