#include <cassert>
#include <boost/asio.hpp>

int main()
{
  using boost::asio::ip::tcp;
  boost::asio::io_service io_service;
  const auto port = 2000;
  tcp::socket socket(io_service, tcp::endpoint(tcp::v4(), port));
  assert(socket.local_endpoint().port() == port);
}
