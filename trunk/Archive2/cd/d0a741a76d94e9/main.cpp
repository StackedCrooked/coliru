#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>

using namespace std; // DON't DO THIS AT HOME

template<class... Args>
class Signal
{
public:

  template<class... CallArgs>
  void operator()(CallArgs&&... args)
  {
    unique_lock<mutex> lock(_mutex);
    auto observers = _observers;
    lock.unlock();

    for(auto&& observer : observers)
    {
      observer(args...);
    }
  }

  template< class Observer > 
  void connect( Observer&& observer )
  {
    unique_lock<mutex> lock(_mutex);
    _observers.push_back( std::forward<Observer>(observer) );
  }

private:
  vector< function<void(Args...)> > _observers;
  mutex _mutex;
};


void print( int value )
{
  std::cout << "BAM: " << value << std::endl;
}

struct Object
{
  void what( int value )
  {
    std::cout << "WHAT: " << value << std::endl;
  }

  void wow( int value )
  {
    std::cout << "WOW: " << value << std::endl;
  }

};

int main()
{
  Signal<int> onBam;

  onBam.connect(&print);

  Object object;
  onBam.connect([&](int k){ object.what(k); });
  
  using namespace std::placeholders;
  onBam.connect(bind(&Object::wow, &object, _1));

  thread observersWorker([&]{
    onBam(42);
    onBam(0);
    onBam(99);
  });
  observersWorker.join();
}

