/*************************************
Simple demo of C++ nullptr
John Dibling
*************************************/

#include <cstdlib>
#include <cstddef>
#include <iostream>
using namespace std;

void foo(int)
{
    cout << "int version called\n";
}

void foo(char*)
{
    cout << "Pointer version called\n";
}

int main()
{
    foo(0);
    foo(nullptr);
}