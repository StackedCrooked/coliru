#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/find.hpp>
#include <boost/variant.hpp>
#include <iostream>

template <class Variant, class Which>
int MAGIC()
{
  size_t pos = boost::mpl::distance
         <typename boost::mpl::begin<typename Variant::types>::type,
          typename boost::mpl::find<typename Variant::types, Which>::type
         >::type::value ;
          
  size_t last= boost::mpl::distance
         <typename boost::mpl::begin<typename Variant::types>::type,
          typename boost::mpl::end<typename Variant::types>::type
         >::type::value;
         
         return pos != last ? pos : -1 ;
}

        
int main()
{
    std::cout << MAGIC< boost::variant<int, float, double, std::string>, float >();
}