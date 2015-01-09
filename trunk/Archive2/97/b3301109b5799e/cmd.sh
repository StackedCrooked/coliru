#title Quiz: can you guess the output of this program?
g++ -std=c++11 main.cpp && ./a.out | sed -e 's,.,\*,g'