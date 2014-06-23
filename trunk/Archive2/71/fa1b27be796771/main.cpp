#include <functional>
#include <map>
#include <iostream>

typedef std::function<void()> TFunc;

struct AClass
{
    int x = 0;
    
    void doStuff()
    {
        std::cout << x << '\n';
    }
};

int main()
{
    std::map<int, TFunc> mFuncMap;
    
    AClass a;
    mFuncMap[42] = std::bind(&AClass::doStuff, &a);
    
    a.x = 5;
    mFuncMap[42]();
}
