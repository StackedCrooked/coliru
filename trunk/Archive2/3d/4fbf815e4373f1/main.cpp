#define BOOST_CHRONO_HEADER_ONLY
#define BOOST_ERROR_CODE_HEADER_ONLY
#include <boost/chrono.hpp>
int main()
{
    boost::chrono::high_resolution_clock c;
    auto diff = c.now() - c.now();

    std::cout << diff;
}
