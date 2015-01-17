#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/utility/string_ref.hpp>

namespace boost
{
    template <>
    inline string_ref
    copy_range<string_ref, iterator_range<char const*>>
      ( iterator_range<char const*> const& r )
    {
        return string_ref( begin(r),  end(r) - begin(r) );
    }
}


int main() 
{
    boost::string_ref str = "test_the_world";
    std::vector<boost::string_ref> strs;
    boost::split(strs, str, boost::is_any_of("_"), boost::token_compress_on);
    for (auto& v : strs)
    {
        std::cout << v << std::endl;
    }
    return 0;
}