#include<iostream>

int main(){
    const int size= 10;
    int** x = new int*[size];
    std::cout << (sizeof(char**) == sizeof(char*));
}