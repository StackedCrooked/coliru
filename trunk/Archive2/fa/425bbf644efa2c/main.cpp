#include <iostream>

namespace detail {
  struct csv_tag { };

  struct csv_impl {
    ~csv_impl () { _stream << "\n"; }
    std::ostream&  _stream;
  };

  struct indirection {
    operator csv_impl const& () {
      return impl._stream << ',', void(), impl;
    }

    csv_impl const& impl;
  };

  template<class T>
  indirection operator<< (csv_impl const& impl, T&& val) {
    return {( impl._stream << val, void(), impl )};
  }

  csv_impl operator<< (std::ostream& os, csv_tag) {
    return { os };
  }
}

namespace { detail::csv_tag csv; }

int main () {
  std::cout << csv << 1 << "hello" << 3.14f;
  std::cout << csv << 0 << "world" << 4.31f;
}