#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;


class C1 
{
    public:
    
    int operator() (int i)
    {
        return (i*i);
    }
    
};

int main()
{
    C1 c;
    std::function<int(int)> f = c;
    vector<int> array={1, 2, 4, 5};

    for (int a : array)
        std::cout << f(a) << std::endl;
}
