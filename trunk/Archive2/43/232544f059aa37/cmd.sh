echo "A=1" ; clang++ -std=c++11 -stdlib=libc++ -DA=1 main.cpp -lsupc++ && echo OK
echo "A=0" ; clang++ -std=c++11 -stdlib=libc++ -DA=0 main.cpp -lsupc++ && echo OK