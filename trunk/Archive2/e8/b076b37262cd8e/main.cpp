
#include <iostream>
#include <functional>

template <typename T>
class LIFOPool
{
    std::function <T*()> factory_;
    //...details irrelevant
public:
    LIFOPool(std::function<T*()> factory = []() { return new T(); }) : factory_(factory) {}
    //...details irrelevant
};

int main()
{
    LIFOPool<int> lf;
}
