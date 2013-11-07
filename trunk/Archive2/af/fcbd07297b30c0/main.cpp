#include <iostream>

struct base {
    virtual const char* what() const noexcept {
        return "base";
    }
};

struct derived : public base {
    virtual const char* what() const noexcept override {
        return "derived";
    }
};

struct anotherderived : public derived {
    virtual const char* what() const noexcept override {
        return "anotherderived";
    }
};

void function()
{
    throw anotherderived();
}

int main() {
    try {
        function();
    }
    catch (const derived &d) {
        std::cerr<<"derived"<<std::endl;
    }
    catch(const base& b) {
        std::cerr <<"base" << '\n';
    }
    
}