#include <cassert>

union T
{
    int x;
    int y;
    
    T& operator=(const T& other)
    {
        x = other.x;
        return *this;
    }
    
    bool operator==(const T& other)
    {
        return x == other.x;
    }
};

int main()
{
    T a{5};
    T b{6};
    
    a = b;
    assert(a==b);
}
