#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <iostream>

template<typename>
struct TD;

template<bool Value, typename Next, typename Last>
struct is_serializable_impl
{
private:
   static const bool cvalue = !boost::is_pointer<typename boost::remove_reference<
      typename boost::fusion::result_of::deref<Next>::type>::type>::value;
public:
   static const bool value = Value && is_serializable_impl<cvalue, typename boost::fusion::result_of::next<Next>::type, Last>::value;
};

template<bool Value, typename Last>
struct is_serializable_impl<Value, Last, Last>
{
   static const bool value = Value;
};

template<typename T>
struct is_serializable : is_serializable_impl<true, typename boost::fusion::result_of::begin<T>::type,
   typename boost::fusion::result_of::end<T>::type>
{
};

template<typename T, typename = void>
struct serializer;

template<typename T>
struct serializer<T, typename boost::enable_if<typename boost::fusion::traits::is_sequence<T>::type>::type>
{
   static_assert(is_serializable<T>::value, "Not serializable");
};

struct simple
{
   int ivalue;
   double dvalue;
};

BOOST_FUSION_ADAPT_STRUCT(
      simple,
      (int, simple::ivalue)
      (double, simple::dvalue)
);

struct with_pointer
{
   int ivalue;
   int* pvalue;
};

BOOST_FUSION_ADAPT_STRUCT(
      with_pointer,
      (int, with_pointer::ivalue)
      (int*, with_pointer::pvalue)
);

int main()
{
   serializer<simple> ss;
   serializer<with_pointer> swp;
}
