#include <iostream>
#include <string>
#include <vector>

template <class... Fields>
class Counter {
 public:
  static Counter<Fields...>* New(const std::string& name, const Fields&... fields) {
      // Do nothing ...
      return new Counter<Fields...>();
  }
};

template<class... Fields>
void CreateCounter(Counter<Fields...>* counter, const Fields&... fields) {
  counter = Counter<Fields...>::New("Counter", fields...);
  // ....
}

int main()
{
    // Creates counter named "Counter".
    Counter<int, std::vector<int>, std::string> my_counter;
    CreateCounter(&my_counter, 42, std::vector<int>(42), std::string("Hello"));
    
    return 0;
}
