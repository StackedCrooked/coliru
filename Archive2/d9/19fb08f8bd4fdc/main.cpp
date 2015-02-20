#include <iostream>
#include <memory>
#include <iterator>
#include <vector>
#include <algorithm>

    class my_iterator :
      public std::iterator<
        std::bidirectional_iterator_tag,
        int, std::ptrdiff_t, int const*, int const&
      >
{
  int d_val;
public:
  my_iterator() : d_val(0) {}
  my_iterator(int val) : d_val(val) {}

  my_iterator  operator--(int) { d_val--; return my_iterator(d_val + 1); }
  my_iterator &operator--()    { d_val--; return *this; }
  my_iterator  operator++(int) { d_val++; return my_iterator(d_val - 1); }
  my_iterator &operator++()    { d_val++; return *this; }

  int const& operator*() const { return d_val; }

  bool operator==(my_iterator const  &o) { return d_val == o.d_val; }
  bool operator!=(my_iterator const  &o) { return d_val != o.d_val ; }
};


int main() {
  std::reverse_iterator<my_iterator> reverse_it_begin(25);
  std::reverse_iterator<my_iterator> reverse_it_end(12);
  std::for_each(reverse_it_begin, reverse_it_end, [](int e){ std::cout << e << ' '; });
  std::cout << '\n';
}