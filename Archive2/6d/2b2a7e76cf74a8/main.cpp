#include <iostream>

struct safe_bool
{
    bool abc;
    
    safe_bool(bool val): abc(val) {}
    
    operator bool() const { return abc; }
    
    template<typename T>
    safe_bool(T) = delete;
};

struct Logic
{
    explicit Logic(bool) {}
    
    Logic(safe_bool) {}
    
    template<typename T>
    Logic(T val): Logic(safe_bool(val)) {}
};

void foo(Logic const & val) {
    // ...
}

int main()
{
    foo(true); // should work
    foo("hello"); // shouldn't work
    foo(15); // shouldn't work
    
    foo(Logic {true}); // should work
    foo(Logic {"hello"}); // should work
    foo(Logic {15}); // should work
}
