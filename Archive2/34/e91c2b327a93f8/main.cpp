#include <iostream>

struct X
{
    template<typename T>
    void processPointer(T* ptr) { std::cout << "Hello!\n"; }

    // error: explicit specialization in non-namespace scope ‘struct X’
    // template<>
    // void processPointer(void*) = delete;

    // fine
    void processPointer(void*) = delete;
};

int main ()
{
    X x;
    x.processPointer<void*>(nullptr);
}
