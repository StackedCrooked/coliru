#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <thread>
#include <chrono>
 
void MTF(std::vector<int>&x,int t){
    int tmp=x[t];
    std::move(x.begin(), x.begin()+t, x.begin()+1);
    x[0]=tmp;
    
}
 
int main() 
{
    std::vector<int> v={1,2,3,4,5};
    // copy() would not compile, because std::thread is noncopyable
    MTF(v,2);// 3
    MTF(v,1);// 1
    MTF(v,1);// 3
    MTF(v,0);// 3
    for (auto t : v) std::cout<<t<<" ";
}