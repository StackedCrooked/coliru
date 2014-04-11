#include <iostream>
#include <string>
#include <vector>

class test
{
    public:
    test(int a)
    {
        _a = a;
    }
    public:
    int _a;
};

class testA : public test
{
public:
    testA(int a):test(a)
    {
    }
    
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    testA *a = new testA(1);
//    int ttest = 3;
    
    //if( (ttest & 2) == 2 )
    {
        std::cout << a->_a << std::endl;
    }
}
