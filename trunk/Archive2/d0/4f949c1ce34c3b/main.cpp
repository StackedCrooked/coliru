#include <cassert>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
class iterator
{
public:
  iterator(T data) : data_(data) {}
  typedef T value_type;
private:
  T data_;
};

template <typename T>
class IntegerRange
{
public:
  
  IntegerRange(T low, T high) : low_(low), high_(high)
  {
    assert(low <= high);
  }

  const iterator<T> begin() const {return iterator<T>(low_); }
  const iterator<T> end() const {return iterator<T>(high_); }

private:
      const T low_, high_;
};

int main(int argc, char** argv) {
    IntegerRange<int> r1(-2, 3);
    std::copy(r1.begin(), r1.end(), std::ostream_iterator<int>(std::cout, " "));  //-2 -1 0 1 2

    IntegerRange<unsigned> r2(0, 6);
    std::copy(r2.begin(), r2.end(), std::ostream_iterator<unsigned>(std::cout, " ")); //0 1 2 3 4
    return 0;
}