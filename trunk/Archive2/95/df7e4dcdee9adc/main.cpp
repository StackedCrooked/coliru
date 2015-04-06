#include <iostream>
#include <unordered_map>

template<typename T>
void func(int i)
{
    std::cout << __PRETTY_FUNCTION__ << " -- " << i << "\n";
}

int main()
{
    using function_t = void(*)(int);
    std::unordered_map<char const*, function_t> map = {{"int", func<int>}, {"double", func<double>}, {"bool", func<bool>}, {"short", func<short>}};
    
    auto exec = [&map](char const* s, int i)
    {
        auto const it = map.find(s);
        if(it != map.end())
        {
            it->second(42);
        }else
        {
            // error?
        }
    };
    
    exec("int", 42);
    exec("double", 21);
}