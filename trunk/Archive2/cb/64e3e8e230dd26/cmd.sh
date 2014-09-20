g++ --version
g++ -std=c++14 -c -Wall -pedantic main.cpp
echo $?
echo ---
clang++ --version
clang++ -std=c++14 -c -Wall -pedantic main.cpp
echo $?