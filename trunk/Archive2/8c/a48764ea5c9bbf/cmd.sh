export OMP_NUM_THREADS=3 && g++-4.8 -std=c++11 -O3 -fopenmp -funroll-loops -pedantic -pthread main.cpp && ./a.out 1000