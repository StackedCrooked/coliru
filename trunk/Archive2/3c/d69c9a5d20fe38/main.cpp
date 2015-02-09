#include <iostream>
#include <boost/asio.hpp>

using namespace std;
namespace asio = boost::asio;

int main() {
    std::cout << asio::ip::tcp::iostream("127.0.0.1", "6769").rdbuf();
}
