#include <iostream>
#include <memory>

template <typename T>
struct Arf {
    T stuff;

    Arf() : stuff() {
        
    }

    int foo () {
        return (int)stuff;
    }

};

template <typename T>
struct Woof {
    T stuff;

    Woof() : stuff() {
        
    }

    int foo () {
        int woofwoof = (int)stuff;
        return woofwoof + 42;
    }

};

struct Virtualize {
    virtual int foo () = 0;
};

template <typename T>
struct TVirtualize : public Virtualize {
    T virtualized;
    
    TVirtualize( T virtualize = T() ) : virtualized(virtualize) {
        
    }
    
    virtual int foo () override {
        return virtualized.foo();
    }
    
};


int main() {
   std::unique_ptr<Virtualize> gotit( new TVirtualize<Woof<int>>( ) );
   std::cout << gotit->foo() << std::endl;
   gotit.reset( new TVirtualize<Arf<float>>() );
   std::cout << gotit->foo() << std::endl;
   
}