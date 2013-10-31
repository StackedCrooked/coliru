#include <iostream>
#include <string>
#include <memory>

class CIF
{
public:
    virtual void print() const = 0;
};

class A
{
public:
A(std::unique_ptr<CIF> c) :
 mC(std::move(c))
{}
void print() const
{
    mC->print();
}

std::string toString() const
{
    return "A";
}

private:
std::unique_ptr<CIF> mC;
};

class C1 : public CIF
{
public:
void print() const override
{
    std::cout << "C1" << std::endl;
}
private:
int a;
};

class C2 : public CIF
{
public:
C2(const A& a) :
  mA(a)
{}
 
void print() const override
{
    std::cout << "C2: mA: " << mA.toString() << std::endl;
}
private:
unsigned char a[64];
const A &mA;
};

class B
{
public:
B(bool which) :
mA(
    which == true ? 
     std::unique_ptr<CIF>(new C1()) : 
     std::unique_ptr<CIF>(new C2(mA))
  )
{}

void print()
{
    mA.print();
}

private:
A mA;
};

int main()
{
    B b(false);
    b.print();
}
