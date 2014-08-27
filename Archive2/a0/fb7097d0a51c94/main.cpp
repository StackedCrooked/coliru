#include<iostream>

int main ()
{
    int a=34;
    const int* ref=&a;
    int* ref2=const_cast<int*>(ref);//tabdil const int* be int*
    *ref2=1;
    std::cout<<a;
}
