#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

template<typename T>
std::string demangle() noexcept /* terminate on throw (fair deal) */ {
    int st;
    char * const p = abi::__cxa_demangle(typeid(T).name(), 0, 0, &st);
    switch (st) {
        case 0: return std::unique_ptr<char, decltype(&std::free)>(p, std::free).get();
        case -1: assert(!"A memory allocation failure occurred."); // no memory = game over
        case -2: assert(!"Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: assert(!"One of the arguments is invalid.");
        default: assert(!"Unexpected demangle status");
    }        
}

struct general_exception : virtual std::exception {
    // implicit move for the 'name' argument? or a copy?
    general_exception(std::string name) : std::exception(), name_(name)  {}
    virtual ~general_exception() throw() {}
    virtual const char* what() const noexcept { return name_.c_str(); }
    std::string name_;
};

template<typename T>
struct concrete_exception : virtual general_exception {
    concrete_exception() : general_exception(demangle<T>()) {}
    virtual ~concrete_exception() throw() {}
};

namespace foo {    
    void bar() {
        struct error {}; // complete type is required by typeid
        throw concrete_exception<error>();
    }
}

int main() {
    try {
        foo::bar();
    }
    catch (const std::exception & exc) {
        std::cerr << exc.what() << std::endl;
    }
}