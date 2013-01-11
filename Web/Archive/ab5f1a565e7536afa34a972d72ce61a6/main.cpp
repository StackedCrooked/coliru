#include<iostream>

int main(){
    const int size= 10;
    int** x = new int*[size]; //I have never seen this ???
    std::cout << (sizeof(char**) == sizeof(char*));
}