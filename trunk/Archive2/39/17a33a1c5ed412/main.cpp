#include <iostream>
#include <functional>

int hello(const char *name)
{
    std::cout << "Hello " << name << "\n";
    return 3;
}

int call(const std::function<int(const char*)>& func, const char *name)
{
    return func(name);
}

int main()
{
    int res = call(hello, "Voronoi");
    
    std::cout << "Function returned " << res << "\n";
    
    return 0;
}
