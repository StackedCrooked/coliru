echo "A=1" ; clang++ -std=c++11 -DA=1 main.cpp && echo OK
echo "A=0" ; clang++ -std=c++11 -DA=0 main.cpp && echo OK