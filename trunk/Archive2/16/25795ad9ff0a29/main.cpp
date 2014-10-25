#include <functional>
#include <iostream>
#include <map>

struct A {
  A (int val) : _data (val) { }

  bool operator< (A const& rhs) const {
    return _data < rhs._data;
  }

  int _data;
};

int main () {
  {
    std::map<A, int, std::less<A>> m;
    m.find ('a');
  }
  
  {
    std::map<A, int, std::less<>> m;
    m.find ('a'); // error
  }
}
