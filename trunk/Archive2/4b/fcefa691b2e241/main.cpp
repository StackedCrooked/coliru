#include <iostream>
#include <memory>
 
int main()
{
    std::unique_ptr<int*> p1(new int(10)); 
    return 0;
}