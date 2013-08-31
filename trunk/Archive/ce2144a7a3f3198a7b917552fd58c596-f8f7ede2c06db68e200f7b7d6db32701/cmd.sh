g++-4.8 -std=c++11 -O3 -pthread -S $1 main.cpp -o - > no_wrap
g++-4.8 -std=c++11 -O3 -pthread -S $1 main.cpp -DUSE_WRAP -o - > yes_wrap
diff -y no_wrap yes_wrap