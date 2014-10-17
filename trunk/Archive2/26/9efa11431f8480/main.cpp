#include <iostream>

template <class T>
class A
{
    int i = 0;
public:
    friend std::ostream& operator<<(std::ostream& os, const A& ai)
    {
        A<double> ad;
        ad.i = 2;
        return os;
    }
};

int main()
{
    A<int> ai;
    std::cout << ai;
}
