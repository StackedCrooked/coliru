#title void_t
try() { $1 -c -Dcompiler="\"$1 fail\"" -std=c++11 main.cpp && echo $1 ftw ; echo ; }; 
try g++; try clang++