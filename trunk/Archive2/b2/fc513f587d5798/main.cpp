#include <boost/type_index.hpp>
#include <iostream>

int main()
{
    int x = 5;
    int & y = x;
    
    std::cout << boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name() << '\n';
    std::cout << boost::typeindex::type_id_with_cvr<decltype(y)>().pretty_name() << '\n';
}
