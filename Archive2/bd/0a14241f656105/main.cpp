#include <iostream>
#include <type_traits>

struct X
{
    template<typename T>
    void processPointer(T* ptr) {
        std::cout << "Hello!\n";
        static_assert(std::is_same<void,T>::value, "Forcing the issue");
    }

    // error: explicit specialization in non-namespace scope ‘struct X’
    // template<>
    // void processPointer(void*) = delete;

    // fine
    void processPointer(void*) = delete;
};

template<>
void X::processPointer<void>(void*) = delete;

int main ()
{
    X x;
    x.processPointer<void>((void*)0);
}
