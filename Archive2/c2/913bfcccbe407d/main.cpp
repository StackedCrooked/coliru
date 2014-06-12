#include <vector>

class Base
{
public:
    std::vector<float> fVec;
};

class Derived : public Base
{
public:
    Derived(std::vector<float> v) : fVec(v)
    {

    }
};
int main() {}