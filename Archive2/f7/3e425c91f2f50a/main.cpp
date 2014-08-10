#include <iostream>
#include <utility>
#include <vector>
#include <string>
 
class Luigi
{
    public:
    Luigi()
    {
        std::cout << "default ctor invoked" << std::endl;
    }
    
    Luigi(int p_value) : myValue(p_value)
    {
        std::cout << "user ctor invoked" << std::endl;
    }
    
    Luigi(const Luigi& other) : myValue(other.myValue)
    {
        std::cout << "copy ctor invoked" << std::endl;
    }
    
    // Simple  assignment operator
    Luigi& operator=(Luigi& other) {
     myValue = other.myValue;
     std::cout << " assignment operator invoked" << std::endl;
     return *this;
    }
    
    // Simple move constructor
    Luigi(Luigi&& arg) : myValue(std::move(arg.myValue)) // the expression "arg" is lvalue
    {
        std::cout << "move ctor invoked" << std::endl;
    } 
    // Simple move assignment operator
    Luigi& operator=(Luigi&& other) {
     myValue = std::move(other.myValue);
     std::cout << " move assignment operator invoked" << std::endl;
     return *this;
    }
    
    int myValue;
};

int GetLuigi(const Luigi& p_obj)
{
    std::cout << "GetLuigi(const Luigi& p_obj)" << std::endl;
    return p_obj.myValue;
}

int GetLuigi(const Luigi&& p_obj)
{
    std::cout << "GetLuigi(const Luigi&& p_obj)" << std::endl;
    return p_obj.myValue;
}
int main()
{
    //Luigi a;
    //std::cout << "Luigi a = '" << a.myValue << "'\n";
    
    Luigi b(10);
    std::cout << "Luigi b = '" << b.myValue << "'\n";
    
    //Luigi c(b);
    //std::cout << "Luigi c = '" << c.myValue << "'\n";
    
    //Luigi d = b;
    //std::cout << "Luigi d = '" << d.myValue << "'\n";
    
    Luigi e;
    e = b;
    std::cout << "Luigi e = '" << e.myValue << "'\n";
    
    Luigi f = std::move(b);
    std::cout << "Luigi f = '" << f.myValue << "'\n";
    
    GetLuigi(f);
    
    GetLuigi(std::move(b));
    
}