#include <string.h>

class abc
{
public:
    float (*a)[10];
    
    abc(){
       a = new float[10][10];
    }
};

int main(){}