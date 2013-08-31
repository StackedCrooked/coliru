#include <iostream>
 
template<unsigned long long T>
struct myFunc {
    enum moo : unsigned long long {
        value = myFunc<T-2>::value + myFunc<T-1>::value
    };
};
 
template<>
struct myFunc<2> {
    enum moo : unsigned long long {
        value = 1
    };
};
 
template<>
struct myFunc<1> {
    enum moo : unsigned long long {
        value = 1
    };
};
 
template<>
struct myFunc<0> {
    enum moo : unsigned long long {
        value = 0
    };
};
 
template<unsigned long long i>
struct fibonacci {
    static void loop() {
        std::cout << myFunc<i>::value << "\n";
        fibonacci<i-1>::loop();
    }
};
 
template<>
struct fibonacci<0> {
    static void loop() {
        std::cout << myFunc<0>::value << "\n";
    }
};
 
int main() {
    fibonacci<92>::loop();
}