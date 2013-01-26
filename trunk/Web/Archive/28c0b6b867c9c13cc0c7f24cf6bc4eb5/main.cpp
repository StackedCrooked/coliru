#include <limits>
#include <iostream>

using std::cout;
using std::endl;

struct s
{
    int n;
    
    int* func() const
    {
        return &n;
    }
};

int main()
{
}
