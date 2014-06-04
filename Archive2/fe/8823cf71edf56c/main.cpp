#include <iostream>
#include <functional>
#include <type_traits>

template <bool B, typename T = void>
struct enable_if {
  typedef T type;
};

template <typename T>
struct enable_if<false, T> {};

template <class T> class A
{
private:
    template <class S>
    typename enable_if<std::is_integral<S>::value>::type a_member() {
        std::cout << "Doing something! :D";
    }

    // template <class S>
    // typename enable_if<std::is_floating_point<S>::value>::type a_member() {
    //     std::cout << "Doing something!
    // }

public:
    void another_member() {
        a_member<T>();
    }
};

int main() {
    A<int> AInt;
    AInt.another_member();

    A<float> AFloat;
    AFloat.another_member();
}