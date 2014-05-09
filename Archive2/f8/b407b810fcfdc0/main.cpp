#include <array>
#include <boost/fusion/include/define_struct_inline.hpp>

BOOST_FUSION_DEFINE_STRUCT_INLINE(
  MyStruct,
  (boost::remove_reference<decltype(std::declval<std::array<int, 3>>())>::type, foo)
)

int main()
{
    MyStruct x;
    static_assert(boost::is_same<decltype(x.foo), std::array<int, 3> >::value, "yup");
}
