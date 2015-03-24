#include <iostream>
#include <memory>
#include <utility>

struct PimplClass {
    PimplClass();
    PimplClass(const PimplClass &other);
    
    PimplClass &operator=(PimplClass other);
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

int main() {
    PimplClass pimpl; //impl 1 created with default constructor
    
    pimpl = {}; //impl 2 created with temporary; swapped with impl 1, which dies here with the temporary
    pimpl = pimpl; //impl 3 created with copy for pass-by-value; impl 2 swapped with it, impl 2 dies
    
    auto pimpl2 = pimpl; //impl 4 created with copy
    
    //impl 3 and impl 4 die here
}

struct PimplClass::Impl {
    Impl() : number(++counter) {std::cout << "Impl " << number << " created.\n";}
    Impl(const Impl &other) : number(++counter) {std::cout << "Impl " << number << " created from Impl " << other.number << '\n';}
    ~Impl() {std::cout << "Impl " << number << " destroyed\n";} 
    
    int number;
    static int counter;
};

int PimplClass::Impl::counter = 0;

PimplClass::PimplClass() : impl_(new Impl) {}

PimplClass::PimplClass(const PimplClass &other) 
    : impl_(new auto(*other.impl_)) {}
    
PimplClass &PimplClass::operator=(PimplClass other) {
    using std::swap;
    swap(impl_, other.impl_);
    return *this;
}