#include <iostream>
#include <typeinfo>

template<class T>
class S
{
    int i = 42;
    
    // not a function template
    friend std::ostream& operator<<(std::ostream& o, S const& p)
    {
        o << "S<"<<typeid(T).name()<<"> - " << p.i;
        return o;
    }
};

int main()
{
    std::cout << S<int>{} << std::endl;
    std::cout << S<double>{} << std::endl;
}
