#include <vector>

class __attribute__ ((visibility ("hidden"))) MyClass
{
public:
    MyClass(){}
    void f1 (){}
};

int main()
{
    std::vector<MyClass> vv;
    return 0;
}
