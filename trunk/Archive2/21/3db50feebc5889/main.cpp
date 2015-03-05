#include <vector>
#include <iostream>

template <class T>
class X {
public:
    std::vector<T> v;
    
    template <class... E>
    X(E&&... e) {
        (void)std::initializer_list<int>{(v.push_back(std::forward<E>(e)), void(), 0)...};
    }
};

int main() {
    X<int> x{1, 2.2};
    std::cout << x.v[0] << ' ' << x.v[1];
}