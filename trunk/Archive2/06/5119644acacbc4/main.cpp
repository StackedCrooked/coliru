#include <iostream>
#include <memory>

namespace {
    struct Foo {
        int a, b, c;
        Foo() : a(1), b(2), c(3) { }
        ~Foo() { std::cout << "~Foo" << std::endl; }
    };

    // Global shared_ptr to Foo instance
    std::shared_ptr<Foo> sFooPtr;

    // The screw up here is that it derefs the ptr nad creates a new "owner"
    void DoPtrIssue(std::shared_ptr<Foo> f) {
        sFooPtr = std::shared_ptr<Foo>(f.get());
    }
   
    // Creates a new shared_ptr and passes to our problematic function
    void CreateGlobalShared() {
        std::shared_ptr<Foo> foo(new Foo());
        DoPtrIssue(foo);
    }
};


int main(int argc, const char* argv[]) {
    CreateGlobalShared();
    std::cout << "b: " << sFooPtr->b << std::endl;
    
    return 0;
}