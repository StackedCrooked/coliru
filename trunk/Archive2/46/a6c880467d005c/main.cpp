#include <iostream>

template<const int a>
class A{ };

const int a = 4;

A<a> b;

void foo(const int a = 4, A<a>); 

int main(){ }