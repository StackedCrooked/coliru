#include <vector>
#include <iostream>

class C
{
public:
    template<typename ...T>
    C(T ...x)
    {
        std::cout << sizeof...(x) << std::endl;
    }
    
    template<typename T>
    C(const std::vector<T>& x)
    {
        std::cout << x.size() << std::endl;
    }
};

int main()
{
    std::vector<int> v;
    
    C a(1, 2, 3);
    C b(v);
}
