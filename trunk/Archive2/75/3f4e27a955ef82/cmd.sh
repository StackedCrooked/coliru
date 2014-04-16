clang++ -Os -std=c++11 -pedantic main.cpp -lboost_system -lboost_program_options
exec 2>&1
./a.out 
./a.out --help
./a.out --c --d
./a.out --c --filename "blablabla.txt"