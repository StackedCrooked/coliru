#include <iostream>
#include <memory>

int main()
{
    using namespace std;
    
    int *i = new int(5);
    
    unique_ptr<int> up1(i);
    unique_ptr<int> up2(i);
    
    return 0;    
}