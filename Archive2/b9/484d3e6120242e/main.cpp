#include <iostream>
#include <boost/smart_ptr/make_shared_array.hpp>

int main()
{
    auto b = boost::make_shared<int[]>(4);
    b[3] = 5;
    std::cout << "B[3]:" << b[3];
}
