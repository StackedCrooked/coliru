#include <cstddef>
#include <iostream>
#include <utility>

template<typename T, std::size_t S>
struct NCons;

struct NNil { };

template<typename T, std::size_t S>
struct NList {
    using type = NCons<T, S>;
};

template<typename T>
struct NList<T, 0> {
    using type = NNil;
};

template<typename T, std::size_t S>
struct NCons {
    NCons(T head_, typename NList<T, S - 1>::type tail_)
        : head(std::move(head_)), tail(std::move(tail_)) { }

    T head;
    typename NList<T, S - 1>::type tail;
};

template<typename T, std::size_t S, typename F>
void for_each(NCons<T, S> const& list, F function) {
    function(list.head);
    for_each(list.tail, function);
}

template<typename F>
void for_each(NNil, F) { }

int main() {
    NCons<int, 3> list(
        1,
        NCons<int, 2>(
            2,
            NCons<int, 1>(
                3,
                NNil()
            )
        )
    );
    for_each(list, [] (int x) { std::cout << x << '\n'; });
    return 0;
}
