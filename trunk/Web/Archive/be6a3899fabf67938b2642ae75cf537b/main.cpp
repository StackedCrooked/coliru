#include <iostream>
#include <tuple>

template<typename >
std::string nameof()
{
    auto sep = std::string(" = ");
    auto sig = std::string(__PRETTY_FUNCTION__);
    return std::string(sig.data() + sig.find(sep) + sep.size(), sig.data() + sig.find(";"));
}


int main()
{
    std::cout << nameof<int>() << std::endl;
    std::cout << nameof<bool>() << std::endl;
    std::cout << nameof<std::string>() << std::endl;
}