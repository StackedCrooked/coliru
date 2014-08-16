g++ -DA    -std=c++11 -shared -fPIC main.cpp -o libA.a;
g++ -DB    -std=c++11 -shared -fPIC main.cpp -o libB.a;
g++ -DMAIN -std=c++11 -ldl          main.cpp;
./a.out