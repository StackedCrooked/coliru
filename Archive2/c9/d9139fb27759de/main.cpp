#include <iostream>
#include <string>
#include <type_traits>
#include <map>

template<class T>
struct Ref {
    Ref() {
        std::cout << "Ref constructed\n";
    }
    ~Ref() {
        std::cout << "Ref destructed\n";
    }
    
    operator int() const & {
        std::cout << "Converting to handle type\n";
        return 0;
    }
};

template<class ReturnType>
struct GetField;

template<>
struct GetField<int> {
    static Ref<int> get() {
        return Ref<int>();
    }
};

template<class T>
struct Field {
    Ref<T> get() {
        return GetField<T>::get();
    }
};

int main() {
    Field<int> test;
    int handle = test.get();
    return 0;
}
