#include <cstddef>

template <typename T> class container {
public:
    class iterator {
        static const std::size_t foo = sizeof(T);
    };
};


template <template <class> class Container, class T>
struct Triple {
  T value;
  typename Container<Triple>::iterator prev, next;
};

Triple<container, int> t;
