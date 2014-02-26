#include <iostream>

int main()
{
    
    int ret = 1;
    printf("Value: %d", ret);
    goto out;
    printf("Value: %d", ret);

out:
    return ret = 2;
    
}



