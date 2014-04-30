#include <iostream>
#include <string>
#include <vector>

class Test
{
public:
    virtual void Do() = 0;
    //virtual ~Test() = 0;
    //virtual ~Test();
};

class ATest : public Test
{
protected:
    int ii;
    
public:
    ATest() : ii(0) {};
    virtual ~ATest() {};
    
    void Do() {ii++; std::cout << ii << std::endl;}
};

int main()
{
    ATest* p = new ATest();
    
    p->Do();
    
    Test* t = p;
    t->Do();
    
    delete p;
}
