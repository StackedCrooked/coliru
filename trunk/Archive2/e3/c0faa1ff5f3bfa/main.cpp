#include <iostream>
#include <typeinfo>

template<class T>
class S;

template<class T>
class inner
{
    T m = 42;
    friend std::ostream& operator<<(std::ostream& o, inner const& p)
    {
        return o << p.m;
    }
};

template<class T>
class S
{
    inner<T> m;
    
    // not a function template
    friend std::ostream& operator<<(std::ostream& o, S const& p) // injected-class-name `S`
    {
        return o << "S<"<<typeid(T).name()<<"> - " << p.m;
    }
};

int main()
{
    std::cout << S<int>{} << std::endl;
    std::cout << S<double>{} << std::endl;
}
