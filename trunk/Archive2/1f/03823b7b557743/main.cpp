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
    template<typename U, typename P = typename boost::remove_reference<U>::type, typename V = typename pair_type<P>::type, typename ret_type = typename boost::disable_if<boost::is_array<V>, V>::type>
    pair<ret_type>& operator=(U&&)
    {
        std::cout << "not array" << std::endl;
        return *this;
    }
    
    template<typename U, typename P = typename boost::remove_reference<U>::type, typename V = typename pair_type<P>::type, typename ret_type = typename boost::enable_if<boost::is_array<V>, V>::type, typename = void>
    pair<ret_type>& operator=(U&&)
    {
        std::cout << "array" << std::endl;
        return *this;
    }
};

int main()
{
    pair<int> a, b;
    b = a;
    
    pair<int[]> c, d;
    c = d;
}
