#include <iostream>
#include <utility>


template<typename T>
struct  Movable
{
    static_assert(std::is_integral<T>::value, "");

    Movable(T&& t) : t(std::forward<T>(t)) {}

    Movable(Movable&& rhs) : t(rhs.t) { rhs.t = T(); }

    Movable& operator=(Movable&& rhs)
    {
        t = rhs.t;
        rhs.t = T();
        return *this;
    }

    Movable(const Movable&) = default;
    Movable& operator=(const Movable&) = default;

    operator T&() { return t; }
    operator const T&() const { return t; }

private:
    T t;
};


typedef Movable<bool> Bool;


int main()
{
    Bool a{true};
    Bool b{true};
    
    auto print = [&]{ std::cout << a << ' ' << b << std::endl; };
    
    // print initial state
    print();
    
    // b -> a
    a = std::move(b);
    print();
    
    // a -> b
    b = std::move(a);
    print();
}
