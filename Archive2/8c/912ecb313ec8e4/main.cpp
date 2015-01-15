#include <iostream>
#include <type_traits>

struct MyBigType {
    MyBigType() = default;
    
    MyBigType(const MyBigType&) {
        std::cout << "copy-ctor ";
    }

    MyBigType(MyBigType&&) {
        std::cout << "move-ctor ";
    }

    MyBigType& operator=(const MyBigType&) {
        std::cout << "copy= ";
        return *this;
    }

    MyBigType& operator=(MyBigType&&) {
        std::cout << "move= ";
        return *this;
    }
};

class MyClass {
  public:
    void f(MyBigType a, int id) {
        this->a_ = std::move(a);
    }
  private:
    MyBigType a_;
};
    
int main() {
    MyClass c;
    MyBigType m;
    c.f(m, 1); // copy ctor, move assign
    std::cout << '\n';
    c.f(MyBigType{}, 1); // move ctor, move assign
}
