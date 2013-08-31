#include<iostream>

// Header file

#include <fstream>
#include <ostream>
#include <string>

template<int size> struct strassen
{
static void strassen_matrix_multiplication(int A[size][size], int B[size][size], int C[size][size]){
  const int n = size / 2; //make this a compile time constant

  int A11[n][n] = {};
  int P1[n][n] = {};
  int S1[n][n] = {};
  strassen<n>::strassen_matrix_multiplication(S1, A11, P1);
}
};

template<> struct strassen<1>  {
static void strassen_matrix_multiplication(int A[1][1], int B[1][1], int C[1][1]){}
};

template<> struct strassen<0>  {
static void strassen_matrix_multiplication(){}
};

int main()
{
    int arr[3][3];
    strassen<3>::strassen_matrix_multiplication(arr, arr, arr);
}