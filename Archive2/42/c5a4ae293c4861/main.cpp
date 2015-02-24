#include <iostream>
 
int main()
{
    int h1 = 0;
    int h2 = 0;
    int nums[] = {1,12,49,12,17,5,0,3,49,2,9,7,11,13};
   
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