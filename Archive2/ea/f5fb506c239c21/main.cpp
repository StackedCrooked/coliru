#include <iostream>
#include <boost/variant.hpp>
#include <type_traits>
#include <stdexcept>

struct A
{
    virtual ~A(){}
    virtual void foo() { }
};
struct B : A
{
    virtual void foo() { std::cout << "B::foo()" << std::endl; }
};

template <typename T>
struct visitor : boost::static_visitor<T>
{
    template <typename U>
    T operator()(U&& u)
    {
        if (std::is_base_of<typename std::remove_pointer<T>::type
                           , typename std::remove_pointer<typename std::decay<U>::type>::type>::value)
        {
            return u;
        }
        throw std::runtime_error{"Invalid type"};
    }
};

template <typename T, typename... Args>
T my_get(boost::variant<Args...>& var){
    
    visitor<T> vis{};
    return boost::apply_visitor(vis, var);
}

int main()
{
    typedef boost::variant<A*,B*> MyVar;
    MyVar var = new B;
    A* a = my_get<A*>(var);
    a->foo();
}
