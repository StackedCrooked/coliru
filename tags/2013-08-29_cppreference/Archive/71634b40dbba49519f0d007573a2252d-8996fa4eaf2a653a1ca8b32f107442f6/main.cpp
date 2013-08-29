#include <vector>

int* f() { return new int; }
char* h() { return new char; }

template <class T>
using generic_pointer = auto (*)() -> T*;

template <class... T>
using generic_vector = std::vector<generic_pointer<T>...>;

int main()
{
    generic_vector<int> p{f, h};
};