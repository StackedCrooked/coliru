#include<iostream>

    int fibo(int n, bool first=true)
    {
        int ret=0;
        if(n>2)
        {
            ret=fibo(n-1,false)+fibo(n-2,false);
        }
        else
        {
            ret=1;
        }
        
        if(first)
        {
            std::cout<<ret<<std::endl;
        }
        return ret;
        
    }
    

int main()
{
    std::cout<<fibo(7)<<std::endl;
}
    