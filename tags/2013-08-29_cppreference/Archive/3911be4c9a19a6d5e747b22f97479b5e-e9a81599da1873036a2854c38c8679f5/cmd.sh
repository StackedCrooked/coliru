printf "\n\n=== ASSEMBLY OUTPUT ===\n"
g++-4.8 -std=c++11 -O3 -pthread main.cpp -S -o - | c++filt

printf "\n\n=== STRACE OUTPUT ===\n"
g++-4.8 -std=c++11 -O3 -pthread main.cpp && strace ./a.out | c++filt