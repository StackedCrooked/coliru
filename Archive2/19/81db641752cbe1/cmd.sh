gcc -x c -DA main.cpp -c -o a.o \
&& gcc -x c -DB main.cpp -c -o b.o \
&& gcc a.o b.o \
&& ./a.out