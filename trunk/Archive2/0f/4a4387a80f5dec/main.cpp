template <typename T>
struct funky_ptr {
    funky_ptr() : p() {}
    funky_ptr(T* t) : p(t) {}
    ~funky_ptr() { delete p; } // no need to check for null

    T*& ref() { return p; }

  private:
    T* p;
};

#include <iostream>

struct X { 
    X()                    { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    ~X()                   { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X(X const&)            { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X(X&&)                 { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X& operator=(X const&) { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; } 
    X& operator=(X&&)      { std::cout << __PRETTY_FUNCTION__ << "\n"; return *this; } 
};

int main()
{
    auto ptr = funky_ptr<X>(new X);

    auto b = ptr;
}
