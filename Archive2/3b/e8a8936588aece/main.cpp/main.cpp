#include <iostream>

int main()
{
    
    int value = 1;
    printf("Value: %d", value);
    goto broken;
    printf("Value: %d", value);

broken:
    return value = 2;
    
}



