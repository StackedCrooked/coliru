#include <iostream>
#include <string>
#include <vector>

class MyClass
{
public:
    MyClass()
    {
        std::cout << "default" << std::endl;
    }
    MyClass(MyClass& other)
    {
        std::cout << "copy" << std::endl;
    }
    MyClass(MyClass&& other)
    {
        std::cout << "move" << std::endl;
    }
    
    MyClass& operator=(MyClass& other)
    {
        std::cout << "assign" << std::endl;
        return *this;
    }
    
    MyClass& operator=(MyClass&& other)
    {
        std::cout << "move assign" << std::endl;
        return *this;
    }
};

void constructorWithRef(MyClass&& rref)
{
    MyClass mine(rref); 
}

void constructorWithRefAndMove(MyClass&& rref)
{
    MyClass mine(std::move(rref));
}

void assignWithRef(MyClass&& rref)
{
    MyClass mine;
    mine = rref;
}

void assignWithRefAndMove(MyClass&& rref)
{
    MyClass mine;
    mine = std::move(rref);   
}

int main(int argc, char* argv[])
{
    {
        MyClass lvalue;    
        constructorWithRef(std::move(lvalue));
    }
    std::cout << "------------" << std::endl;
    {
        MyClass lvalue;
        constructorWithRefAndMove(std::move(lvalue));
    }
    std::cout << "------------" << std::endl;
    {
        MyClass lvalue;
        assignWithRef(std::move(lvalue));
    }
    std::cout << "------------" << std::endl;
    {
        MyClass lvalue;
        assignWithRefAndMove(std::move(lvalue));
    }
    
    
    return 0;
}