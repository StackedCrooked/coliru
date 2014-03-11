#include <map>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/units/detail/utility.hpp>
#include <boost/smart_ptr.hpp>

struct BaseMessage {};
struct DerivedMessage : BaseMessage {};

template<class T, class F>
void invoke_binder(F const& f, BaseMessage const& m)
{
    f( static_cast<T const&>(m) );
}

std::map<std::string, boost::function<void(BaseMessage const&)> > subscribers;

template <typename Type, class F>
void ask(F const& f)
{
        std::cout << "Asking for " << boost::units::detail::demangle(typeid(Type).name()) << std::endl;
        subscribers[boost::units::detail::demangle(typeid(Type).name())] = boost::bind(&invoke_binder<Type, F>, f, _1);;
}

void testBase(BaseMessage const&)
{
        std::cout << "In testBase" << std::endl;
}

void testDerived(DerivedMessage const&)
{
        std::cout << "In testDerived" << std::endl;
}

int main()
{
        ask<BaseMessage>(&testBase);
        ask<DerivedMessage>(&testDerived);
}