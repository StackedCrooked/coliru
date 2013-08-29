#include <iostream>
#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>

void fun(int num)
{
    std::cout << "Hello Atul  num:" <<  num << "\n";
}

int main()
{
    boost::function<void (int)> f;
    //int num=0;
    f = boost::bind(fun, 40);
    //num = 10;
    f(76);
    std::cout << "Hello India\n";
}

