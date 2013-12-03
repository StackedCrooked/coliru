#include <memory>
#include <iostream>

template <typename T>
class X {
    typedef std::initializer_list<T> listInit;
    T sharedPtr;
public:
    explicit X(const T& shPtr) {
        sharedPtr = shPtr;
        std::cout << sharedPtr << std::endl;
    }
    explicit X(listInit shPtrs) {
        for (const auto& li : shPtrs) {
            std::cout << li << std::endl;    
        }
    }
};

int main () {
    auto shared = std::make_shared<int>(12);
    X<decltype(shared)> x(shared);
    return 0;
}
