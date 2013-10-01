#include <iostream>

struct base {
    virtual void bar() {
        std::cout << "base" << std::endl;   
    }
    virtual ~base() = default;    
};

struct extra {
  void foo() {
    std::cout << "extra" << std::endl;   
  }
};

struct derived : public base, public extra {
  void bar() override {
    std::cout << "derived" << std::endl;   
  }
};

int main() {
    derived d;
    base *b = &d;
    if (auto e = dynamic_cast<extra*>(b)) {
        e->foo(); 
        return 1;
    }
    std::cout << "oh no!" << std::endl;
}