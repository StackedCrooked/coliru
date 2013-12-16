#include <iostream>
#include <typeinfo>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/zip_view.hpp>

namespace fuz = boost::fusion;

typedef fuz::vector2<int,int> vec1;
typedef fuz::vector2<char,char> vec2;
typedef fuz::vector2<vec1&, vec2&> sequences;

typedef fuz::zip_view<sequences> zip_view_type;

typedef fuz::result_of::zip<vec1, vec2>::type zip_result_type;

BOOST_MPL_ASSERT((boost::is_same<zip_view_type, zip_result_type>));

int main()
{
    std::cout << typeid(zip_view_type).name() << std::endl;
    std::cout << typeid(zip_result_type).name() << std::endl;
    
    std::cout << "vector<int,int> is not the same as vector2<int,int>" << std::endl;
    std::cout << typeid(fuz::vector<int,int>).name() << std::endl;
    std::cout << typeid(fuz::vector2<int,int>).name() << std::endl;
}