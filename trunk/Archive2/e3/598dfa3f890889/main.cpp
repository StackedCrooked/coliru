#include<iostream>

int main()
{
    int i = 10;
    int* p = &i;
    delete p;
    return 0;
}