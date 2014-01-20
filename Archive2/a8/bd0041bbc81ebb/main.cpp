#include <iostream>

template<typename T>
class A
{  
public:
    template<typename innerT>
    class B
    {
    };
  
    template<typename innerT>
    friend bool operator==(A::B<innerT> & one, int two)
    { return true; }

    template<typename innerT>
    friend bool operator==(int one, A::B<innerT> & two)
    { return false; }
};

int main()
{
    A<float>::B<double> b;
    std::cout << (b == 2) << " is different from " << (2 == b);
}
