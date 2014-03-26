#include <iostream>
#include <string>
#include <vector>

class xxx
{
    public:
    
    int **triangle;
    
    
    xxx(int n){
        triangle = new int *[n+1];
        for(int i=0;i<=n; i++) triangle[i]=new int[i+1];
    }
    
};


int main()
{
    xxx x(10);
    std::cout << "OK" << std::endl;
}
