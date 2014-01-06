#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <string>

BOOST_FUSION_DEFINE_STRUCT
(
    (), Widget,
    (int, field1)
    (std::string, field2)
)

template<typename Struct>
size_t hash_value(const Struct &x)
{
    return boost::fusion::fold(x, size_t(0), [](size_t hash, const auto &x)
    {
        boost::hash_combine(hash, x);
        return hash;
    });
}

int main()
{
    Widget y, x = {1, "1"};
    y.field1 = 2;
    y.field2 = "2";
    std::cout << hash_value(x) << " " << hash_value(y) << std::endl;
}