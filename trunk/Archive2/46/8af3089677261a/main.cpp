#include <iostream>

template <typename T>
struct Wrapper
{
    T* ptr;
    std::size_t length;
};

template <typename T>
Wrapper<T> make_wrapper(T* ptr, std::size_t len) {return {ptr, len};}

template <typename T>
T* begin(Wrapper<T> w) {return w.ptr;}

template <typename T>
T* end(Wrapper<T> w) {return begin(w) + w.length;}

int main()
{
    int a[] = {1, 2, 3};

    for (auto i : make_wrapper(a, sizeof a / sizeof *a))
    std::cout << i << ", ";
}