// Type your code here, or load an example.
#include <iostream>
#include <stdio.h>

int main()
{
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
        {
    		printf("%3d", i*j);
        }
		printf("\n");
    }
    return 0;
}