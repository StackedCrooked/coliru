#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/type_traits.hpp>


#include<iostream>

using namespace boost::mpl;

typedef map<
    pair<int_<0>, int>,
    pair<int_<1>, float>
    > TestMap;
    
struct ceva
{
    void operator()(int)
    {
        std::cout << "from int" <<std::endl;
    }
    
    void operator()(float)
    {
        std::cout << "from char" <<std::endl;
    }
};

struct IsInvalid
{
    template<typename T>
    struct apply
    {
        typedef typename boost::is_same<typename T::first, int_<0>>::type type;
    };
};

typedef filter_view<TestMap, IsInvalid>::type NotZero;

int main()
{
    ceva c;
    c(second<deref<begin<TestMap>::type>::type>::type());
    c(deref<NotZero>::type::second() );
    return 0;
}