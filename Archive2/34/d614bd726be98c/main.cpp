#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

using namespace std;

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
    cout << "test..." << endl;
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