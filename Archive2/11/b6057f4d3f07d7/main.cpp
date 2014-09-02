#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Duck
{
    std::string const str = "quack";
    public:
    Duck()
    {
        std::cout << "construct" << std::endl;
    }
    ~Duck()
    {
        std::cout << "destroy" << std::endl;
    }
    void quack()
    {
        [this](){ std::cout << str << std::endl; }();
    }
};

int main()
{
    Duck duck;
    std::function<void()> func = [&](){ duck.quack(); };
    func();
    
    std::function<int(int)> factorial = [&](int x) { return (x==1) ? 1 : (x * factorial(x-1)); };
    std::cout << factorial(3);
    
    std::initializer_list<int> iii = {1,2,3,4};
    std::initializer_list<int> const& yyy = iii;
}
