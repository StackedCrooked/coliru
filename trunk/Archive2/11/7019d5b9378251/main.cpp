#include <iostream>
#include <functional>
#include <vector>

class NoCopy
{
public:
    NoCopy() {}
    int operator()(int) const { return 42; }
    
private:
    NoCopy(const NoCopy& r) = delete;
};

int main()
{
    std::function<int()> fn(NoCopy());
    
    std::cout << fn(0) << std::endl;
}
