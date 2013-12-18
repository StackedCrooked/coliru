#include <iostream>

using namespace std;

class MyClass
{
public:
    MyClass(initializer_list<double> il)
    {}
    
    MyClass(int, string){}

};

int main()
{
    MyClass m{10, 10.1};
    
    auto ii = int{1};
    

    return 0;
}