#include <iostream>
#include <vector>
#include <initializer_list>

template<typename T>
class Wrapper {
private:
    std::vector<T> k;
public:
    Wrapper(std::initializer_list<T> l): k(l) {
    }
    Wrapper() {}
    size_t length() {
        return k.size();
    }
    T operator[](size_t n) {
        return k[n];
    }
};

int main() {
    Wrapper<int> v = {1,2,3,4,5,6};
    std::cout << "Length: " << v.length() << " \noperator[] test: " << v[3];
}