g++ -O2 main.cpp -DA=1 -S -o - | c++filt > a
g++ -O2 main.cpp -DB=1 -S -o - | c++filt > b
diff -y a b