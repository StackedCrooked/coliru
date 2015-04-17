#include <cstddef> // for NULL
#include <iostream>
#include <vector>

class null_value_type;

template <class container_type>
struct container_traits {
  typedef const typename container_type::value_type* pointer_type;
  static pointer_type get_array_pointer(const container_type& c) {
    return &c[0];
  }
};

class null_value_type {
 public:
  operator int*() {
    return NULL;
  }

  template <class container_type>
  friend null_value_type container_traits<container_type>::get_array_pointer();
 private:
  null_value_type() {}
};

struct null_type {};

template <>
struct container_traits<null_type> {
  typedef null_value_type pointer_type;
  static pointer_type get_array_pointer(const null_type& c) {
    return null_value_type();
  }
};

template <class container_type>
typename container_traits<container_type>::pointer_type
get_array_pointer(const container_type& c) {
  return container_traits<container_type>::get_array_pointer(c);
}

int main() {
  std::vector<int> v(3);
  const int *p1 = get_array_pointer(v);
  if (p1 == &v[0]) std::cout << "(1) Success.\n";
  
  const int *p2 = get_array_pointer(null_type());
  if (p2 == NULL) std::cout << "(2) Success.\n";
  return 0;
}
