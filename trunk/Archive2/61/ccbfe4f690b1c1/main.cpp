#include <iostream>
#include <boost/asio.hpp>

using namespace std;
namespace asio = boost::asio;

int main() {
    std::cout << asio::ip::tcp::iostream("localhost", "6767").rdbuf();
}
