g++-4.6 -v | grep "gcc version" \
&& g++-4.6 -std=c++03 -DA main.cpp -c -o a.o \
&& g++-4.6 -std=c++03 -DB main.cpp -c -o b.o \
&& g++-4.6 -std=c++03 a.o b.o