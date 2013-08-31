#include <utility>

template<typename T>
class movable
{
public:
    movable() : mT() {}
    
    movable(const movable<T> & rhs) : mT(std::move(rhs.mT))
    {
    }
    
    movable<T>& operator=(const movable<T> & rhs)
    {
        mT = std::move(rhs.mT);
        return *this;
    }
        
    movable(movable<T>&&) = default;
    movable& operator=(movable<T>&&) = default;
    
private:     
    T mT;
};


int main()
{
    movable<int> m;
    movable<int> n = std::move(m);
    
    auto l = [m, n](){};
    l();
}