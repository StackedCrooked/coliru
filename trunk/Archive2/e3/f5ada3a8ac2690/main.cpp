
#include <iostream>

class MyClass {
    
public:

    // Constructor declaration
    MyClass()
    {
        std::cout << "on MyClass constructor" << std::endl;
    }
    
    // Destructor declaration
    ~MyClass()
    {
        std::cout << "on MyClass destructor" << std::endl;
    }
};

int main()
{
    MyClass myClassInstance;
}
