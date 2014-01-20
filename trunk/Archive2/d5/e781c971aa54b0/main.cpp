#include <iostream>
#include <type_traits>

struct X
{
    template<typename T>
    void processPointer(T* ptr) {
        std::cout << "Hello!\n";
        static_assert(std::is_same<void,T>::value, "Forcing the issue");
    }
};

template<> void X::processPointer<void>(void*) = delete;

int main ()
{
    X x;
    x.processPointer<void>((void*)0);
}
