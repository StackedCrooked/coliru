#include <iostream>

class abc
{
    int value_;
public:
    abc() { value_ = 3;  }
    int value() const { return value_fr(*this); }

    friend int value_fr(const abc& var){ return var.value_; }
};

int main()
{
    abc obj;
    std::cout<<obj.value();
    return 0;
}
