#include <iostream>
#include <string>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

template <typename T>
T bar(const int) 
{
  BOOST_STATIC_ASSERT_MSG(!boost::is_same<T, std::string>::value, 
                          "T cannot be std::string");
  return T();
}

int main()
{
    bar<int>(10);
    bar<std::string>(10);  // fails static assertion
}
