#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int arr[4] = {1,2,3,4};
    int arr2[4] = {5,6,7,8};
    int **arrPtr = new int*[2];

    arrPtr[0] = arr;
    arrPtr[1] = arr2;
    typedef int* (*arrPtrRealType)[2];
    typedef int (*arrRealType)[4];

    for (int *a : *(arrPtrRealType)(arrPtr)){
        for (int i : *(arrRealType)(a)){
            cout << i << endl;
        }
    }
}