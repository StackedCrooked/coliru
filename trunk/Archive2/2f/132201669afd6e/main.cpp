#include <iostream>
#include <string>
#include <boost/signals2.hpp>

struct Hello 
{
  void operator()() const
  {
    std::cout << "Hello";
  }
};

struct World
{
  void operator()() const
  {
    std::cout << ", World!" << std::endl;
  }
};

int main()
{
     boost::signals2::signal<void ()> sig;

    sig.connect(Hello());
    sig.connect(World());
    
    sig();
}
