#include <iostream>

struct Foo
{
    Foo(): x_(0), y_(x_) {}
    
    void setX(int x) { x_ = x; }
    
    const int& y_;
private:
    int x_;
};

int main()
{
    Foo f;
    
    std::cout << f.y_ << std::endl;
    f.setX(2);
    std::cout << f.y_ << std::endl;
    
    return 0;
}