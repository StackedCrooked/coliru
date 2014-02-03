g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread -DA main.cpp -c -o a.o \
&& g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread -DB main.cpp -c -o b.o \
&& g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread a.o b.o \
&& ./a.out