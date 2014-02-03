#include <iostream>
using namespace std;

int main(){
    int arr[4] = {1,2,3,4};
    int arr2[4] = {5,6,7,8};
    int **arrPtr = new int*[2];

    arrPtr[0] = arr;
    arrPtr[1] = arr2;

    for (int *a : *(int*(*)[2])(arrPtr)){
        for (int i : *(int (*)[4])(a)){
            cout << i << endl;
        }
    }
}