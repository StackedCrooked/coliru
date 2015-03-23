#include <array>
#include <boost/fusion/include/define_struct_inline.hpp>
#include <boost/utility/identity_type.hpp>

BOOST_FUSION_DEFINE_STRUCT_INLINE(
  MyStruct,
  (typename BOOST_IDENTITY_TYPE((std::array<int, 3>)), foo)
)

int main()
{
    MyStruct x;
    static_assert(boost::is_same<decltype(x.foo), std::array<int, 3> >::value, "yup");
}
