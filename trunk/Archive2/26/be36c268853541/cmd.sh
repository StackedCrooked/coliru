#title Stack generating routes
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | perl -pe 's,_<,(,g; s/,\s?>/)/g; s,\s?>,),g'