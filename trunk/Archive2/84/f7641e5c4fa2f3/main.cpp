#include <iostream>

class Foo
{
public:
    Foo(int k)
    : i(k)
    {}

    int i;
    
    int operator() () {return i;}
};

int main ()
{ 
    int i = 5;
    Foo** array = new Foo*[i];
    
    for (int j = 0; j < i; ++j)
    {
        array[j] = new Foo(j);
        std::cout << (*array[j])() << std::endl;
    }
    
    std::cout << "this worked!\n";
}