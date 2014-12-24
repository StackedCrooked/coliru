#include <iostream>
#include <boost/signals2/signal.hpp>

int main()
{
  boost::signals2::signal<void ()> sig;
  boost::signals2::signal<void (const char*)> done;

  done.connect([](char const* name)
  {
      std::cout<<"Hi "<<name<<"!"<<std::endl;
  });

  sig.connect([&done]()
  {
      char const* name="Dave";
      std::cout<< "Hello. My name is "<<name<<" and I'm an alcoholic."<<std::endl;
      done(name);
  });
  
  sig.connect([]()
  {
      std::cout<< "I peed my pants."<<std::endl;
  });

  // Call all of the slots
  sig();
  
  return 0;
}
