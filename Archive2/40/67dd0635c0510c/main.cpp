#include <functional>
#include <iostream>
#include <vector>
#include <boost/any.hpp>

typedef int (*f)(int);
typedef double (*b)();

int foo(int i) { return i * 2; }

double bar() { return 42.42; }

void bar2() { std::cout << "bar2\n"; }

int main() 
{
    std::vector<boost::any> v; // vectors of functions
    
    v.push_back(&foo);
    v.push_back(&bar);
    
    std::function<void(void)> b2 = &bar2;
    v.push_back(b2);
     
    std::cout << boost::any_cast<f>(v[0])(42) << '\n';
    std::cout << boost::any_cast<b>(v[1])() << '\n';
    boost::any_cast< std::function<void(void)> >(v[2])();
}