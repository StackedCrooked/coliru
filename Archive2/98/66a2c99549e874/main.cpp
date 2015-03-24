#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct PimplClass {
    PimplClass();
    PimplClass(PimplClass &&);
    ~PimplClass();
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

int main() {
    std::vector<PimplClass> pimpls;
    for (int i = 0; i < 5; ++i) {
        pimpls.push_back(PimplClass());
    }
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
PimplClass::PimplClass(PimplClass &&) = default;
PimplClass::~PimplClass() = default;