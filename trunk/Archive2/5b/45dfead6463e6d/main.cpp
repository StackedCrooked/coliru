#include <iostream>

int DrawSomething(bool bar)
{
    int result = 0;
    
    if (bar)
    {
        result |= -1;
    }
    
    return result;
}

int main()
{
    int result = DrawSomething(true);
    
    std::cerr << result << std::endl;
 
    return 0;
}