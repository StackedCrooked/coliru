#include <iostream>
#include <string>
#include <array>

template<class T>
struct RefImpl {
    int handle;
};

template<class T>
class Ref : public RefImpl<Ref<T>> {
};

template<>
class Ref<int> : public RefImpl<Ref<T>> {
    public:
        operator std::string() const {
            return handle;
        }
};

int main() {
    //Ref<int> foo;
    //std::cout << foo << "\n";
}