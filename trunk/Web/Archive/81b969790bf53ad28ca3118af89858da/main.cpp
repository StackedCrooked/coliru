#include<iostream>

// Header file

#include <fstream>
#include <ostream>
#include <string>

template<int size> struct strassen
{
void strassen_matrix_multiplication(int A[size][size], int B[size][size], int C[size][size]){
  const int n = size / 2; //make this a compile time constant

  int A11[n][n] = {};
  int P1[n][n] = {};
  int S1[n][n] = {};
  strassen_matrix_multiplication(S1, A11, P1);
}
};

template<> struct strassen<1>  {
void strassen_matrix_multiplication(int A, int B, int C){}
};

template<> struct strassen<0>  {
void strassen_matrix_multiplication(){}
};

int main()
{
    int arr[3][3];
    strassen<3> s;
    s.strassen_matrix_multiplication(arr, arr, arr);
}