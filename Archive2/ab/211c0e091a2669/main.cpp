#include <tuple>
#include <vector>
#include <type_traits>

// 1
template <typename T>
void func_(T&& t, long) { /* ... */ }

// 2
template <typename TupleType,
          std::size_t Size=std::tuple_size<std::decay_t<TupleType>>::value>
void func_(TupleType&& tup, int) { /* ... */ }

template <typename T>
void func(T&& t) { func_(std::forward<T>(t), 0); }

int main() {
    int i;
    std::vector<int> v;
    auto t = std::make_tuple(1, 2.0, 'a');
    auto p = std::make_tuple(1, 2.0);

    func(i); // calls 1
    func(v); // calls 1

    func(t); // ambiguous, should call 2
    func(p); // ambiguous, should call 2
}