export OMP_NUM_THREADS=4 && g++ -std=c++11 -O3 -fopenmp -funroll-loops -pedantic -pthread main.cpp && ./a.out 1000