#include <iostream>
#include <string.h>

struct Base
{
    void clear() { memset(this, 0, sizeof(Base)); } 
    
private:
    long l;
    int i;
};

struct Derived : public Base
{
    int get() const { return f; }
    void set(int n) { f = n; }
    int f;
};

int main()
{    
    Derived d;
    d.set(1);
    d.clear();
    std::cout << d.get() << std::endl;
}