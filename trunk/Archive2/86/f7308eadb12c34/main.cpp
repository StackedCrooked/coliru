#include <iostream>
#include <vector>

template <typename Cont>
void print(Cont& c)
{
    for (auto it = c.begin(); it != c.end(); ++it)
        std::cout << *it << "  ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> v{1,2,3,4,5,6,7};
    
    print(v);
    
    //return 0;
}