g++-4.8 -std=c++11 -S main.cpp -o a &&
g++-4.8 -std=c++11 -S -O2 main.cpp -o b &&
diff -y a b