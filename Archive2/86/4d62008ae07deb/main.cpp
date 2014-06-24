#include <algorithm>
#include <array>
#include <iostream>
#include <string>


int a_count = 0;

class A {
  public:
    A () {
        count_ = ++a_count;
        std::cout << "default " << count_ << std::endl;
    }
    
    A (const A& rhs) {
        count_ = ++a_count;
        std::cout << "copy " << count_ << std::endl;
    }
    
    ~A () {
        std::cout << "destructor " << count_ << std::endl;
    }
    
    void f () const {
        std::cout << "function call " << count_ << std::endl;
    }
  private:
    int count_;
};

int main () {
    std::cout << "begin" << std::endl;
    A a;
    
    std::cout << "before anonymous function" << std::endl;
    auto func = [=] () {
        std::cout << "anonymous function begin" << std::endl;
        a.f();
        std::cout << "anonymous function end" << std::endl;
    };
    std::cout << "defined anoymous function" << std::endl;
    func();
    std::cout << "end" << std::endl;
}
