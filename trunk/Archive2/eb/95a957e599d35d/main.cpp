#include <iostream>

template<class T>
class A
{
public:
    struct Y; //declaration
    struct U{ int v; };  //definition
};

A<int> a;

int main(){ }