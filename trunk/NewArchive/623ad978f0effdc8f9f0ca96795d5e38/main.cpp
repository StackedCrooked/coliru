#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

struct MyClass
{
    std::string name;
    
    MyClass(const std::string n): name(n) { }
    MyClass(const char* n): name(n) { }
};

int main()
{
    std::vector<MyClass> v{"John", "Ben", "Alison", "Sleepy", "Grumpy"};
    
    std::sort(v.begin(), v.end(), [](const MyClass& c1, const MyClass&c2)->bool { return c1.name.compare(c2.name) < 0; });
    
    for(auto const& c: v)
        std::cout<<c.name<<std::endl;
}