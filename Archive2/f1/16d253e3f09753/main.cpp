#include <iostream>
#include <boost/variant.hpp>
#include <type_traits>
#include <stdexcept>

struct A
{
    virtual ~A(){}
    virtual void foo() { std::cout << "A::foo()" << std::endl; }
};
struct B : A
{
    virtual void foo() { std::cout << "B::foo()" << std::endl; }
};

template <typename T>
struct visitor : boost::static_visitor<T>
{
private:
    using Base = typename std::remove_pointer<
                        typename std::remove_cv<
                            typename std::remove_reference<T>::type
                        >::type
                    >::type;
                        
    template <typename U>
    T get(U& u, std::true_type) const
    {
        return u;
    }
    
    template <typename U>
    T get(U& u, std::false_type) const
    {
        throw boost::bad_get{};
    }

public:
    template <typename U>
    T operator()(U& u) const
    {
        using Derived = typename std::remove_pointer<
                            typename std::remove_cv<
                                typename std::remove_reference<U>::type
                            >::type
                        >::type;
                        
        using tag = std::integral_constant<bool, (std::is_base_of<Base, Derived>::value
                                                 || std::is_same<Base, Derived>::value)
                                                 && std::is_convertible<U, T>::value>;
        return get(u, tag{});
    }
};

template <typename T, typename... Args>
T my_get(boost::variant<Args...>& var)
{
    return boost::apply_visitor(visitor<T>{}, var);
}

int main()
{    
    boost::variant<A*,B*> var = new B;
    
    A* a = my_get<A*>(var); // works!
    a->foo();
    
    B* b = my_get<B*>(var); // works!
    b->foo();
}
