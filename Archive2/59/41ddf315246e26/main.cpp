#include <iostream>
#include <boost/type_traits.hpp>

template <typename T>
class pair;

template <typename T>
struct pair_type;

template <typename T>
struct pair_type<pair<T>> { using type = T; };

template <typename T>
class pair
{    
public:

   //default constructors. one for non-array types and one for arrays. These work.
   template <typename temp_type = T>
   pair(typename boost::disable_if<boost::is_array<temp_type>>::type* /*ignore*/ = 0)
      : first(T())
      , second(T())
   {}

   template <typename temp_type = T>
   pair(typename boost::enable_if<boost::is_array<temp_type>>::type* ignore = 0)
   {}
    
   template<typename U, typename P = typename std::remove_reference<U>::type, typename V = typename pair_type<P>::type, typename ret_type = typename boost::disable_if<boost::is_array<P>, V>::type>
   pair<ret_type>& operator=(U&& rhs)
   {
       std::cout << "whooo! I am a template!" << std::endl;
       this->first = rhs.first;
       this->second = rhs.second;
       return *this;
   }
    
   T first;
   T second;
};

int main()
{
    pair<int> a, b;
    b = a;
}
