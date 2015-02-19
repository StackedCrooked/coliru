#include<algorithm>
#include <iostream>
#include <memory>
#include <iterator>
#include <vector>


struct special_int{
    int i;
    operator int&() { return i; }
    operator const int&() const { return i; };
    special_int(int i = 0) : i(i) {}
    ~special_int() { i = 0xDEADBEEF; }
};

class my_iterator : public std::iterator<std::bidirectional_iterator_tag, int> {
  std::shared_ptr<special_int> d_val;
public:
  my_iterator() : d_val(std::make_shared<special_int>(0)) {}
  my_iterator(int val) : d_val(std::make_shared<special_int>(val)) {}
  // default cc and mc calling default cc and mc of shared_ptr
 
  my_iterator  operator--(int) {
      auto it = my_iterator(*this); //cc of shared_ptr
  	d_val = std::make_shared<special_int>(*d_val - 1); // copy on write
  	return it;
  }
  my_iterator &operator--()    {
  	d_val = std::make_shared<special_int>(*d_val - 1); // copy on write
  	return *this;
  }
  my_iterator  operator++(int) {
  	auto it = my_iterator(*this); //cc of shared_ptr
  	d_val = std::make_shared<special_int>(*d_val + 1); // copy on write
  	return it;
  }
  my_iterator &operator++() {
  	d_val = std::make_shared<special_int>(*d_val + 1); // copy on write
  	return *this;
  }
 
  int &operator*() { return *d_val; }
 
  bool operator==(my_iterator const  &o) { return *d_val == *o.d_val; }
  bool operator!=(my_iterator const  &o) { return *d_val != *o.d_val ; }
};
 
 
int main() {
 
  std::vector<int> vec;
  std::copy(std::reverse_iterator<my_iterator>(5), std::reverse_iterator<my_iterator>(), std::back_inserter(vec));
  for(auto &e : vec)
    std::cout << e << ' ';
  std::cout << '\n';
}