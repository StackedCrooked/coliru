#include <iostream>

struct B {
    virtual ~B() = default;  
};

struct D : B {
    ~D();  
};

D::~B() {}