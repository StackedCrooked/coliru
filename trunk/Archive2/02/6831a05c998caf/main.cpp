#include <iostream>
#include <vector>

class AIf1
{
public:
    virtual void a1() const  = 0;
};

class AIf2
{
public:
    virtual void a2() const = 0;
};

class A : public AIf1, public AIf2
{
public:
    A(int a) : mA(a) {}
    void a1() const override { std::cout << "a1" << std::endl; }
    void a2() const override { std::cout << "a2" << std::endl; }
private:
    int mA;
};

class AIf1Processor
{
public:
   void addA(const AIf1 &aif1) { ma.push_back(&aif1); }
   void use() { for (auto &a : ma ) { a->a1(); } }
private:
    std::vector<const AIf1 *> ma;
};

class AIf2Processor
{
public:
   void addA(const AIf2 &aif2) { ma.push_back(&aif2); }
   void use() { for (auto &a : ma ) { a->a2(); } }
private:
    std::vector<const AIf2 *> ma;
};


int main()
{
    std::vector<A> aVector;
    AIf1Processor p1;
    AIf2Processor p2;
    
    aVector.push_back(A(1));
    p1.addA(aVector.back());
    p2.addA(aVector.back());
    
    aVector.push_back(A(2));
    p1.addA(aVector.back());
    p2.addA(aVector.back());
    
    p1.use();
    p2.use();
}
