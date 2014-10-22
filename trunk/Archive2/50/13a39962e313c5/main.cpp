#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

class test
{
public:
  test()
  {
    io.post(boost::bind(&test::print, this));
    t = boost::thread(boost::bind(&boost::asio::io_service::run, &io));
  }
    
  ~test()
  {
    if (t.joinable())
      t.join();  
  }

  void print()
  {
    std::cout << "test..." << std::endl;
  }

private:
  boost::thread t;
  boost::asio::io_service io;
};

int main()
{
  test();
  return 0;
}