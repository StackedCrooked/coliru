g++ -O3 main.cpp -DBRANCH_PREDICT=0 -masm=intel -march=core2 -S -o - | c++filt > a
g++ -O3 main.cpp -DBRANCH_PREDICT=1 -masm=intel -march=core2 -S -o - | c++filt > b
diff -y a b