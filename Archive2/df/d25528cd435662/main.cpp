#include <iostream>
#include <iterator>

struct loud
{
    int i = 12;
    loud() { std::cout << "loud() at " << (void*)this << "\n"; }
    loud(loud const&) { std::cout << "loud(loud const&) at " << (void*)this << "\n"; }
    ~loud() { std::cout << "~loud() at " << (void*)this << "\n"; }
};

class my_iterator : public std::iterator<std::bidirectional_iterator_tag, int> {
  loud d_val;
public:
  my_iterator  operator--(int) { std::cout << "decrement--\n"; return my_iterator(); }
  my_iterator &operator--()    { std::cout << "--decrementing " << (void*)&d_val << "\n"; return *this; }
  my_iterator  operator++(int) { std::cout << "increment++\n"; return my_iterator(); }
  my_iterator &operator++()    { std::cout << "++increment\n"; return *this; }

  int &operator*() { std::cout << "*dereferencing " << (void*)&d_val << "\n"; return d_val.i; }

  bool operator==(my_iterator const  &o) { return false; }
  bool operator!=(my_iterator const  &o) { return true ; }
};


int main() {
  auto it = std::reverse_iterator<my_iterator>();
  std::cout << "between construction of reverse iterator and dereference\n";
  int &i = *it;
  std::cout << i << '\n';
}