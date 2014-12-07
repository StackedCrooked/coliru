#include <iostream>
#include <functional>
#include <vector>

class NoCopy
{
public:
    NoCopy() {}
    int  operator() (int ii) const { return 42; }
    
private:
   // NoCopy(const NoCopy& r) = delete;
};

int main()
{
    typename std::function<int(int)> fn = std::move(NoCopy());
    
    std::cout << (fn(0)) << std::endl;
}
