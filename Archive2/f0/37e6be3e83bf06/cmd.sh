echo "A=1" ; clang++ -c -std=c++11 -stdlib=libc++ -DA=1 main.cpp && echo OK
echo "A=0" ; clang++ -c -std=c++11 -stdlib=libc++ -DA=0 main.cpp && echo OK