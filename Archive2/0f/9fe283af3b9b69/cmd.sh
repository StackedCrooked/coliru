g++ -std=c++11 -O3 main.cpp -DARRAY && (./a.out; echo "main (array) returned: $?");
g++ -std=c++11 -O3 main.cpp && (./a.out; echo "main (vector) returned: $?")