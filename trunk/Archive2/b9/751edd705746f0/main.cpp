#include <functional>
#include <iostream>
 
int f(int, int) { return 1; }
int g(int, int) { return 2; }
int h(int, int) { return 3; }
std::string test(std::function<int(int, int)> const& arg)
{
    std::string name;
    
    if (arg.target<std::plus<int>>())
        name = "plus";
    else if (arg.target<std::minus<int>>())
        name = "minus";
    else
    {
        int (*const* ptr)(int, int) = arg.target<int(*)(int, int)>();
        if (ptr && *ptr == f)
            name = "f";
        else if (ptr && *ptr == g)
            name = "g";
    }
    
    return name;
}
 
int main()
{
    const std::function<int(int, int)> a[] = {
        std::function<int(int, int)>(),
        std::function<int(int, int)>(std::plus<int>()),
        std::function<int(int, int)>(std::minus<int>()),
        std::function<int(int, int)>(f),
        std::function<int(int, int)>(g),
        std::function<int(int, int)>(h) };
        
    for (const auto& b : a)
    {
        std::cout << "test function: ";
        
        if (b)
        {
            std::string name = test(b);
            const char *quotes = "\"";
            if (name.empty())
            {
                name = "unknown";
                quotes = "";
            }
                
            std::cout << "is " << quotes << name << quotes << ".  " << name << "(2, 4) = " << b(2, 4);
        }
        else
        {
            std::cout << "is empty";
        }
        
        std::cout << std::endl;
    }
}