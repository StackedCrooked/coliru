#include <vector>

template <unsigned int N>
struct priority_helper
    : public priority_helper<N-1> {};

template <>
struct priority_helper<0U> {};

template <unsigned int N>
using priority = int priority_helper<N>::*;

constexpr priority<0> by_priority{};

template < class T, class... Args >
auto update_callable_detail(
    priority<1>,
    const std::vector<T>& objects,
    Args&& ... args )
    -> decltype(std::declval<const T&>()(std::forward<Args>(args)...), void())
{
    for ( const T& obj : objects )
        obj( std::forward<Args>(args)... );
}

template < class T, class... Args >
auto update_callable_detail(
    priority<2>,
    const std::vector<T>& objects,
    Args&& ... )
    -> decltype(std::declval<const T&>()(), void())
{
    for ( const T& obj : objects )
        obj();
}

template < class T, class... Args >
void update_callable_detail(
    priority<3>,
    const std::vector<T>&,
    Args&& ... )
{
}

template < class T, class... Args >
void update_callable( const std::vector<T>& objects, Args&& ... args )
{
    update_callable_detail( by_priority, objects, std::forward<Args>(args)... );
}

#include <iostream>

struct X {
    void operator()(int m, int n) const
    { std::cout << "X::operator()(" << m << ", " << n << ")\n"; }
    void operator()() const { std::cout << "X::operator()()\n"; }
};

struct Y {
    void operator()() const { std::cout << "Y::operator()()\n"; }
};

struct Z {};

int main() {
    std::vector<X> xv(2);
    std::vector<Y> yv(2);
    std::vector<Z> zv(2);
    
    update_callable( xv, 4, 5 );
    update_callable( yv, 4, 5 );
    update_callable( zv, 4, 5 );
}
