#include <iostream>
#include <functional>
#include <string>

int hello(const std::string& name)
{
    std::cout << "Hello " << name << "\n";
    return 3;
}

int call(const std::function<int(const std::string&)>& func, const std::string& name)
{
    return func(name);
}

int main()
{
    int res = call(hello, "Voronoi");
    
    std::cout << "Function returned " << res << "\n";
    
    return 0;
}
