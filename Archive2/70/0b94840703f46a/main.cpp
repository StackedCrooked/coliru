#include <initializer_list>
#include <iostream>

template<typename T>
bool any_of(const T& t, std::initializer_list<T> l) {
    for(auto&& i : l) {
        if(i == t) {
            return true;
        }
    }
    return false;
}

int main() {
    if(any_of(10, {1,2,3,4,5,10,14})) {
        std::cout << "...";
    }
}