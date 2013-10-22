echo "C++03:"
g++-4.8 -std=c++03 -O2 -Wall -pedantic main.cpp && ./a.out
echo -e "\nC++11:"
g++-4.8 -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out