#include <boost/asio.hpp>
#include <iostream>

int main()
{
    boost::asio::streambuf a,b;
    std::iostream as(&a);

    as << &b;

    int i, j, k;
    as >> i >> j >> k;
}
