#include <iostream>
#include <string>

class object {
public:
    object(bool a)
    {
        if (a)
            std::cout << "Oh, hi!\n";
    }
    object(const object& b)
    {
        std::cout<<"copy!";
    }
    
}; /* class object */


int main()
{
    //object o;
    object o=true;
    return 0;
}
