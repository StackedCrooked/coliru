#include <iostream>
 
int main()
{
    long long j;
    for (int i = 0; i < 4; ++i)
		j +=  i*1000000000;
        
    std::cout << j << std::endl;
}