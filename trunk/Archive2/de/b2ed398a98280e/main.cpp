#include <boost/asio.hpp>
#include <ostream>

int main()
{
    boost::asio::streambuf a,b;
    std::ostream as(&a);

    as << &b;
}
