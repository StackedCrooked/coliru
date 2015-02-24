#include <iostream>
#include <limits>
 
int main()
{
    int h1 = std::numeric_limits<int>::min();
    int h2 = std::numeric_limits<int>::min();
    int nums[] = {-29, -12, 37};
   
    for (int i : nums)
    {
        if (i > h1)
        {
           h2 = h1;
           h1 = i;
        }
        else if (i > h2 && i < h1)
           h2 = i;
    }
 
    std::cout << "2nd highest is: " << h2 << std::endl;
 
    return 0;
}