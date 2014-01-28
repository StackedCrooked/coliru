ln -sfn /Archive2/d5/4e5d8c8a5d5b3c/main.cpp json.hpp
ln -sfn /Archive2/6e/071e2127ca5e54/main.cpp json.cpp
clang++ -std=c++11 -Os -Wall -pedantic main.cpp json.cpp && ./a.out