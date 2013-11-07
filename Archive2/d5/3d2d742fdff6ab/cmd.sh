g++ -std=c++11 -O2 -S main.cpp -o O2
g++ -std=c++11 -O3 -S main.cpp -o O3
diff.py -m O2 O3