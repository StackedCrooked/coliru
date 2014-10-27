#include <iostream>
#include <utility>

template<typename Target, typename F>
Target recycle_any_and_apply(Target&& lhs, Target&& rhs, F f)
{
    std::cout << "rvalue + rvalue\n";
    return f(std::move(lhs), std::move(rhs));
}

template<typename Target, typename Rhs, typename F>
Target recycle_any_and_apply(Target&& lhs, Rhs&& rhs, F f)
{
    std::cout << "rvalue + lvalue\n";
    return f(std::move(lhs), std::forward<Rhs>(rhs));
}

template<typename Target, typename Lhs, typename F>
Target recycle_any_and_apply(Lhs&& lhs, Target&& rhs, F f)
{
    std::cout << "lvalue + rvalue\n";
    return f(std::move(rhs), std::forward<Lhs>(lhs));
}

template<typename Target, typename Lhs, typename Rhs, typename F>
Target recycle_any_and_apply(Lhs const& lhs, Rhs const& rhs, F f)
{
    std::cout << "lvalue + lvalue\n";
    return f(Target(lhs), rhs); // copy, bind to reference, move to return value (cannot be elided)
}


struct foo
{
    int i;
    foo& operator*=(foo const& x)
    {
        i *= x.i;
        return *this;
    }
};

template<typename T, typename U>
foo operator*(T&& t, U&& u)
{
    // move from return value to return value (can be elided)
    return recycle_any_and_apply<foo>(std::forward<T>(t), std::forward<U>(u), [](foo&& lhs, foo const& rhs) -> foo&& { return std::move(lhs *= rhs); });
}

int main()
{
    foo l = {42};
    auto lvalue = [&]() -> foo& { return l; };
    using rvalue = foo;
    
    lvalue() * lvalue();
    lvalue() * rvalue();
    rvalue() * lvalue();
    rvalue() * rvalue();
}