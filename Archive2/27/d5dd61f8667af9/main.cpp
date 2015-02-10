#include <iostream>

class test
{
public:
    explicit test(int v)
    :
        value(v)
    {}
    
    ~test()
    {}

    test &operator=(test &&self)
    :
        value(self.value)
    {
        return *this;
    }
    
    int value;
}

int main()
{
    test a(123);
    test b = a;
}