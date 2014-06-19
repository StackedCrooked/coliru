#include <vector>
#include <iostream>

class trytemplate
{
public:
    //////// 1
    template <typename T>
    trytemplate(const T& p)
    {
        std::cout << p << std::endl;
    }

    //////// 3
    template <template<typename...> class V, typename... Params>
    trytemplate(const V<Params...>& p)
    {
        std::cout << p[0] << " " << p.size() << std::endl;
    }
};

int main()
{
    int i = 123;
    trytemplate o1(i); // call ctor 1
    
    std::vector<float> v1(1, 123.0f);
    trytemplate o2(v1);
}
