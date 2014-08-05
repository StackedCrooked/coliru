#include <iostream>
#include <map>
#include <cstdint>
#include <sstream>

struct Temp { 
    int a = 10;
    Temp() { }
    Temp(int a) : a(a) { }
};

struct Foo { 
    Temp t;
    Foo() { }
    Foo(int a) : t(Temp(a)) { }

    void DoSomething() { std::cout << "A: " << t.a << std::endl; }
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
        b.foo.t.a = 25;

        f = &b.foo;
        
        std::cout << "IsNull: " << ptr.IsNull() << std::endl;
    }
    { 
        Bar c;
        c.foo.t.a = 10;
    }
    
    std::cout << "IsNull: " << ptr.IsNull() << std::endl;
    ptr.Access();
    
	return 0;
}