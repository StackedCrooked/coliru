#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <list>
#include <algorithm>


template<class T>
void function(T t)
{
    std::cout << "function template\n";
}

template<>
void function<int>(int a)
{
    std::cout << "function<int> specialization\n";
}
/*

void function(int a)
{
    std::cout << "function(int)\n";
}
*/


void function(double a)
{
    std::cout << "function(double)\n";
}
int main()
{
    function(3);
    function(4.3);
}

