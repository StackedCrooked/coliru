#include <initializer_list>
#include <utility>
#include <string>
#include <iostream>

std::string str(const char* t)
{
    return t;
}

template <typename T>
std::string str(const T& t)
{
    return std::to_string(t);
}

struct AgnosticMap
{
    AgnosticMap(std::nullptr_t) : isnull(true) {}
    
    template <typename T, typename U>
    AgnosticMap(T t, U u)
    {
        a = str(t);
        b = str(u);
    }
    
    template <typename T, typename U>
    AgnosticMap(T t, std::initializer_list<U> il)
    {
        a = str(t);
        for (auto& u : il)
        {
            b += str(u) + ", ";
        }
    }
    
    std::string a, b;
    bool isnull = false;
};

void foo(AgnosticMap a1, AgnosticMap a2 = nullptr, AgnosticMap a3 = nullptr, AgnosticMap a4 = nullptr)
{
    std::cout << a1.a << " " << a1.b << std::endl;
    if (!a2.isnull) std::cout << a2.a << " " << a2.b << std::endl;
    if (!a3.isnull) std::cout << a3.a << " " << a3.b << std::endl;
    if (!a4.isnull) std::cout << a4.a << " " << a4.b << std::endl;
}

int main()
{ 
    foo({"Blargh", "Bleh"});
    foo({"Biz", 43.6});    
    foo({"Blargh", "Bleh"}, {"Biz", 43.6}, {"Bam", {43, 43, 43}});
}
