#include <iostream>

class abc;
int value(const abc& var);

class abc
{
    int value_;
public:
    abc() { value_ = 3;  }
    int value() const { return ::value(*this); }

    friend int value(const abc& var){ return var.value_; }
};

int main()
{
    abc obj;
    std::cout<<obj.value();
    return 0;
}
