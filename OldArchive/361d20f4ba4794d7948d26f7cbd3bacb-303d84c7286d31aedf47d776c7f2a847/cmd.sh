g++-4.8 -DEARLY_RETURN -std=c++11 -O3 -Wall -pthread -S main.cpp -o a.asm
g++-4.8 -std=c++11 -O3 -Wall -pthread -S main.cpp -o b.asm
diff -y a.asm b.asm