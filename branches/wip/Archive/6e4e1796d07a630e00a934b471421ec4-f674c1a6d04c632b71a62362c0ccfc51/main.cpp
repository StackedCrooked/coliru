#include <iostream>
#include <thread>
 
void threadFunction()
{
     for (int i = 0;i < 10; i++)
        std::cout<<i<<" ";
    std::cout<<"HERE"<<std::endl;
}
 
int main()
{
     std::thread thr(threadFunction);
     //std::cout<<"a"<<std::endl;
     thr.detach();
     std::cout<<"a"<<std::endl;
     return 0;
}