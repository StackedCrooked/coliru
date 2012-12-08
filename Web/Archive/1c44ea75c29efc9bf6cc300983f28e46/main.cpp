#include <utility>

template<typename T>
class movable
{
public:
    movable() : mT() {}
    
    movable(const movable<T> & rhs) : mT(std::move(rhs.mT)) { }
    T mT;
};


int main()
{
    movable<int> m;
    movable<int> n = std::move(m);
    
    auto l = [m, n](){};
    l();
}