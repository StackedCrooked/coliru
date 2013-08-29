#include <iostream>
#include <string>
#include <vector>

class A
{
    int n; 
    std::vector<int> v;
public: 
    A(int _n) : n(_n), v(n) //<- wrong
    {}
};


int main()
{
    A a(10);
}
