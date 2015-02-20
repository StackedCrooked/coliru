#include <iostream>
#include <utility>

constexpr const char* foo(double d)
{
    static std::pair<double, const char*> arr[] = { { 1.0, "Apple" }, { 2.0, "Pear" }, { 3.0, "Orange" } /* more stuff */ };
    for (auto& p : arr)
    {
        if (d == p.first)
            return p.second;
    }
    
    return "";
}

int main()
{
    std::string s = foo(3.0);
    std::string s2 = foo(4.0);
    
    std::cout << s << " " << s2 << std::endl;
    return 0;
}