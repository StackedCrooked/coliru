#include <cstddef>
#include <iostream>

template <typename T, std::size_t N>
size_t arraySize(T const (& array)[N]) {
    return (sizeof(array)/sizeof(T));
}

using namespace std;

int main(){

int arr1[20];
char arr2[20];
double arr3[20];

cout << arraySize(arr1) << ' ' << arraySize(arr2) << ' ' << arraySize(arr3) << endl;
cout << sizeof(arr1)/sizeof(int) << ' ' << sizeof(arr2)/sizeof(char) << ' ' << sizeof(arr3)/sizeof(double);

}