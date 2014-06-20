#include <iostream>
#include <string>

void trace(const std::string& msg) { std::cout << msg << std::endl; }
class CB
{
public:
    CB() { trace("CB ctr"); }
    ~CB() { trace("CB dtr"); }
};

// abstract class
class AB: public CB
{
public:
    AB() { trace("AB ctr"); }
    virtual ~AB() { trace("AB dtr"); }
    virtual void doSt() = 0; // an abstract method
};

class Test: public AB 
{
public:
    Test() { trace("Test ctr"); }
    ~Test() { trace("Test dtr"); }
    void doSt() {};
};

int main()
{
    Test t;
}
