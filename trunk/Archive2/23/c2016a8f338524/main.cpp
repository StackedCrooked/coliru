#include <type_traits>

template <typename...>
struct _and : std::true_type {};
template <typename First, typename...Rest>
struct _and<First, Rest...> :
  std::conditional<First::value, _and<Rest...>, std::false_type>::type {};

template<typename T, int... shape>
class Array
{
    template <typename> using int_t = int;
public:
    T& operator () (decltype(shape)...args);
};

int main() {
    Array<int, 2, 3, 4> a;
    a(0,0,0);
}
