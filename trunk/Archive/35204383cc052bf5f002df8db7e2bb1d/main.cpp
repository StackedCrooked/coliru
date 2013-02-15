#include<iostream>

// Header file

#include <fstream>
#include <ostream>
#include <string>

template<int size>
    void strassen_matrix_multiplication(int (A*)[size], int (B*)[size], int (C*)[size]){
      int n = size / 2;
    
      int A11[n][n];
      int P1[n][n];
      int S1[n][n];
      strassen_matrix_multiplication(S1, A11, P1);
    }

int main()
{
    int arr[2][3];
    strassen_matrix_multiplication(arr, arr, arr);
}