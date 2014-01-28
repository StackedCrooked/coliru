#include <iostream>
#include <string>

class AA
{
public:
    AA() = default;
    virtual void print() const { std::cout << aa << "\n";}

private:
    std::string aa = "AA";
};

class BB : public AA
{
public:
    BB() = default;
    virtual void print() const override {std::cout << bb << "\n"; }

private:
    std::string bb = "BB";
};

int main()
{
    AA aa;  BB bb;
    AA& r = aa; r.print();

    r = bb;
    r.print();
    
    if(&aa == &r) {
        std::cout << "r still refers to aa" << std::endl;
    }
    
    return 0;
}