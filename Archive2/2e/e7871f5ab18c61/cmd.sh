set -x;
g++-4.9 -std=c++11 -O3 -Wall -Wextra -pedantic -pthread main.cpp -lboost_system -lboost_program_options
./a.out --wavelength=10 --energy=20 --frequency=30
./a.out --wavelength=10 --energy=20
./a.out --wavelength=10
./a.out --energy=20