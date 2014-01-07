#include <vector>

template<typename T>
struct allocator_wrapper : T { using T::T; };

template<class T, class A = std::allocator<T>>
using other_vector = std::vector<T, allocator_wrapper<A>>;

template<class T>
void f(std::vector<T>& ) {}

template<class T>
void f(other_vector<T>& ) {}

int main()
{
    other_vector<int> b;
    f(b);
    return 0;
}
