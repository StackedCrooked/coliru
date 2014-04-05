#include <memory>
#include <boost/asio.hpp>

int main()
{
    struct { float a, b; } arr[10];

    auto mutable_buffer = boost::asio::buffer(arr);
}
