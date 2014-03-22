echo "12 23.3 34.89 100.4 89 23
234.4 99.9 200 123.56" > employees.txt && g++ -std=c++11 -pedantic -W -Ofast -o salary main.cpp && ./salary <<< "6"