g++ -std=c++11 -shared -fPIC -DA main.cpp -o libA.a;
g++ -std=c++11 -shared -fPIC -DB main.cpp -o libB.a;
g++ -std=c++11 -DMAIN -ldl main.cpp;
./a.out