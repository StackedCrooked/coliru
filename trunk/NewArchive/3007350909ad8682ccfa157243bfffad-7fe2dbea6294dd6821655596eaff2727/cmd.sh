g++ --version
g++ -DUSE_IOSTREAM -O2 main.cpp -S -o - > a
g++ -O2 main.cpp -S -o - > b
diff -y a b