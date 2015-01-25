
class Base 
{
public:
    virtual ~Base() {}
    virtual void unused() = 0; 
};

class Derived
:
public Base
{
public:
    ~Derived(); 
};

int main() {
    Derived d; 

    return 0;
};
