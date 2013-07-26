g++ -std=c++11 -DA -O3 -S main.cpp -o - > a
g++ -std=c++11 -DB -O3 -S main.cpp -o - > b
diff -y a b