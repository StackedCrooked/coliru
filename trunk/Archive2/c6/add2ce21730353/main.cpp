#include <iostream>
#include <typeinfo>

template<class T>
class S;

template<class T>
class inner
{
    T m = 42;
    friend std::ostream& operator<<(std::ostream& o, S<T> const& p);
};

template<class T>
class S
{
    inner<T> m;
    
    // not a function template
    friend std::ostream& operator<<(std::ostream& o, S const& p) // injected-class-name `S`
    {
        o << "S<"<<typeid(T).name()<<"> - " << p.m.m;
        return o;
    }
};

int main()
{
    std::cout << S<int>{} << std::endl;
    std::cout << S<double>{} << std::endl;
}
