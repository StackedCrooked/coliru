clang++ -std=c++11 -Os -Wall -pedantic -lboost_system -lboost_filesystem main.cpp -o test
touch {a..m}.grb2
./test
sleep 1
touch k.grb2
./test