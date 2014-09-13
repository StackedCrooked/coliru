#include <boost/function.hpp>
#include <iostream>


int main()
{
    std::cout << sizeof(boost::detail::function::function_buffer) << std::endl;
}
