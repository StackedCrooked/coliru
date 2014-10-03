#include <vector>
#include <functional>
#include <iostream>

void func1(const std::string& value)
{
    std::cout << "func1 " << value << std::endl;
}

void func2(const std::string& value, int min, int max)
{
    std::cout << "func2 " << value << " " << min << " " << min << std::endl;
}

class X
{
public:
    void x1(const std::string& value)
    {
        std::cout << "X::x1 " << value << std::endl;
    }

    void x2(const std::string& value, int min, int max)
    {
        std::cout << "X::x2 " << value << " " << min << " " << min << std::endl;
    }
};

int main()
{
    X x{};
    const std::vector<std::function<void(std::string)>> functions
    {
        func1,
        std::bind(func2, std::placeholders::_1, 5, 6),
        std::bind(&X::x1, &x, std::placeholders::_1),
    //  ~~~~~~~~^ ~~~~~^  ~^            ~~~~~~~~~~^
    //     bind  function with object  and actual additional argument to be forwarded
    };
    
    for (auto& f : functions)
    {
        f("foo");
    }
}
