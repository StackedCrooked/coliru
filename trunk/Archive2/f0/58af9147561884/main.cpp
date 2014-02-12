#include <iostream>
#include <boost/mpl/int.hpp>
#include <boost/mpl/max.hpp>

template<size_t d> 
struct SomeType
: 
    boost::mpl::int_<d> 
{};

template<size_t d1, size_t d2>
typename boost::mpl::max<SomeType<d1>, SomeType<d2> >::type
Func(SomeType<d1> A, SomeType<d2> B) 
{
    return typename boost::mpl::max<SomeType<d1>, SomeType<d2> >::type();
}

int main()
{
    SomeType<2> st2;
    SomeType<3> st3;
    boost::mpl::max<SomeType<2>, SomeType<3> >::type res = Func(st2, st3);
    std::cout << res.value;
}    
