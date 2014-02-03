#include <iostream>
#include <memory>
using namespace std;

int main(){
    int arr[4] = {1,2,3,4};
    int arr2[4] = {5,6,7,8};
    unique_ptr<int*[]> arrPtrHolder(new int*[2]);
    int **arrPtr = arrPtrHolder.get();

    arrPtr[0] = arr;
    arrPtr[1] = arr2;

    for (int *a : *(int*(*)[2])(arrPtr)){
        for (int i : *(int (*)[4])(a)){
            cout << i << endl;
        }
    }
}