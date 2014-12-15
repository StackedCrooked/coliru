#include <boost/mpl/list.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/tti/has_member_function.hpp>

#include <iostream>
#include <memory>

BOOST_TTI_HAS_MEMBER_FUNCTION(f2)

class Base
{
public:
    virtual double f1(double, double) const
    {
        std::cout << "Called Base Method\n";
        return 0.0;
    }
};

template<typename Derived>
class A : public Base
{
    double f1_impl(boost::mpl::true_, double x, double) const
    {
        std::cout << "Called Derived Method\n";
        return static_cast<const Derived*>(this)->f2(x);
    }
    double f1_impl(boost::mpl::false_, double x, double y) const
    {
        return Base::f1(x, y);
    }

public:
    double f1(double x, double y) const override
    {
        using has_f2 = typename has_member_function_f2
            < Derived
            , double
            , boost::mpl::list<double>
            , boost::function_types::const_qualified
            >::type;
        return f1_impl(has_f2{}, x, y);
    }
};

class B : public A<B>
{
public:
    double f2(double) const
    {
        return 1.0;
    }
};

class C : public A<C>
{
};

int main()
{
    std::unique_ptr<Base> base_instance( new B );
    std::cout << base_instance->f1(100.0, 10.0) << '\n';

    B b_instance;
    std::cout << b_instance.f1(100.0, 10.0) << '\n';
    
    base_instance = std::unique_ptr<Base>{new C};
    std::cout << base_instance->f1(100.0, 10.0) << '\n';
}
