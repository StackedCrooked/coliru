#include <iostream>
#include <boost/asio/streambuf.hpp>

class A {
  public:
    void foo();
  private:
    boost::asio::streambuf cmdStreamBuf_{};
};

void A::foo() {
  std::istream is1{&cmdStreamBuf_}; // works
  auto is2 = std::istream{&cmdStreamBuf_}; // does not compile
}