#include <cstring>

template <int N> struct some_type;

template <>
struct some_type<4> {
    int value = 0;
};

int main() {
  return some_type<std::strlen("test")>().value;
}
