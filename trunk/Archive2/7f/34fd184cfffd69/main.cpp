#include <new>
#include <iostream>
#include <cassert>

struct new_context {
    new_context(const char* file, const int line)
        : file_(file), line_(line) { std::cout << __FUNCTION__ << "," << file << ":" << line << std::endl; scope_ = this; }
    ~new_context() { scope_ = 0; std::cout << __FUNCTION__ << std::endl; }
    static new_context const& scope() { assert(scope_); return *scope_; }
    operator bool() const { return false; }

    const char* file_;
    const int line_;
private:
    static new_context* scope_;
};

new_context* new_context::scope_ = 0;

void* operator new (std::size_t size) throw (std::bad_alloc) {
    std::cout 
        << "operator new" 
        << "," << new_context::scope().file_ 
        << ":" << new_context::scope().line_ 
        << std::endl;
    return 0;
}

void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw() {
    std::cout 
        << "operator new nothrow" 
        << "," << new_context::scope().file_ 
        << ":" << new_context::scope().line_ 
        << std::endl;
    return 0;    
}

#ifndef new
#define new new_context(__FILE__, __LINE__) ? 0 : new
#endif

struct Foo {};

int main() {
    Foo *p;
    p = new Foo;
    p = new Foo[10];
    p = new (std::nothrow) Foo;
    new (p) Foo;
    //p = (Foo*) ::operator new(sizeof(Foo)); // direct invocation of the operator
}