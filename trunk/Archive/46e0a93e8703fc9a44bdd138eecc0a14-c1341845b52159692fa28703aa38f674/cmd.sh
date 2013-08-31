g++-4.8 -std=c++11 -O3 -DINLINE='inline' main.cpp -S -o inline
g++-4.8 -std=c++11 -O3 -DINLINE='' main.cpp -S -o no_inline
diff -y inline no_inline