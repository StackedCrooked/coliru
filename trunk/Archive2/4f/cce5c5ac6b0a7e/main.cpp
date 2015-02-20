#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int ballno1 = 0;
    
    srand(time(NULL));
    int num1gen=(rand()%49+1);
    
    
    ballno1 = ballno1 + num1gen;
    cout<<ballno1<<" ";
}