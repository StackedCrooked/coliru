#include <type_traits>

template<class T>
struct A {
    T operator-() {
        static_assert(!std::is_unsigned<T>::value, "NO");
        return -v;
    }
    T v;
};

int main() {
    A<unsigned> a;
    a=a;
    
    A<int> b;
    -b;
}

#include <vector>
#include <memory>

template class std::vector<std::unique_ptr<int>>;