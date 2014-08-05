#include <iostream>
#include <map>
#include <cstdint>
#include <sstream>

struct Foo { 
    int a = 10;
    Foo() { }
    Foo(int a) : a(a) { }

    void DoSomething() { std::cout << "A: " << a << std::endl; }
};

struct Bar {
    Foo foo;
};

struct PtrWrapper {
    PtrWrapper(Foo*& foo) : foo(&foo) { }

    bool IsNull() const { return *foo == nullptr; }

    void Access() { (*foo)->DoSomething(); }

    private: Foo** foo;
};

int main(int argc, char* argv[]) {
    Foo* f = nullptr;
    PtrWrapper ptr(f);

    {
        Bar b;
        b.foo.a = 25;

        f = &b.foo;
        
        std::cout << "IsNull: " << ptr.IsNull() << std::endl;
    }
    Bar c;
    
    std::cout << "IsNull: " << ptr.IsNull() << std::endl;
    ptr.Access();
    
	return 0;
}