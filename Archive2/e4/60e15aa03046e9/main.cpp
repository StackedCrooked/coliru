#include <iostream>
#include <boost/system/error_code.hpp>



int main(int argc, char* argv[])
{
    boost::system::error_code err;
    std::cout << std::boolalpha << (err == boost::system::errc::success) << std::endl;
}
