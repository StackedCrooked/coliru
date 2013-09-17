#include <iostream>

template<class T>
class S
{
    int i = 42;
    
    // not a function template
    friend std::ostream& operator<<(std::ostream& o, S const& p)
    {
        o << p.i;
        return o;
    }
};

int main()
{
    std::cout << S<int>{};
}
