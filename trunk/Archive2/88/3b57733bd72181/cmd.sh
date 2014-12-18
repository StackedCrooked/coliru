echo O2
g++ -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo O2 no-elide-constructors
g++ -O0 -fno-elide-constructors -Wall -pedantic -pthread main.cpp && ./a.out