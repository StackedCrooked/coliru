#include <iostream>
#include <boost/type_traits.hpp>

template <typename T>
class pair
{    
public:    
    pair& operator=(pair const& rhs)
    {
        return assign(rhs, boost::is_array<T>());
    }
   
private:
    pair& assign(pair const&, boost::true_type)
    {
        std::cout << "array" << std::endl;
        return *this;
    }
   
    pair& assign(pair const&, boost::false_type)
    {
        std::cout << "not array" << std::endl;
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
