struct aggr
{
    int : 2;
    int a[2];
};

#include <iostream>
int main()
{
    aggr x = {{42, 21}};
    std::cout << x.a[0] << std::endl;
    
    std::cout << sizeof(int[2]) << " vs. " << sizeof(aggr);
}
