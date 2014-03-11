#include <type_traits>
#include <iostream>

template<class T>
T make(T&)
{
    return T( std::is_const<T>{} );
}

struct foo
{
private:
    foo(std::true_type)
    {
        std::cout << "made as const\n";
    }
    
    foo(std::false_type)
    {
        std::cout << "made as non-const\n";
    }
    
    template<class T>
    friend T make(T&);
};

int main()
{
    foo const x = make(x);
    foo y = make(y);
}