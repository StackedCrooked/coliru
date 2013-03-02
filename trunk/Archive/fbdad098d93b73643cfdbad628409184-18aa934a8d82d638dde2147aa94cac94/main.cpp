#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <algorithm>
 using namespace std;
 
 
    std::queue<int> q;
    std::mutex m;
    std::condition_variable_any cv; 
    
    
    long pow(long i, long j) {
        if (j ==0) return 1;
        if (j ==1) return i;
        
        if(j%2 == 1){
            i *= i; j--;
        }
            
        return pow(i, j/2) * pow(i,j/2);
    }
int main()
{  
    for(auto i=0;i<7;++i)
     cout<<pow(3,i)<<endl;
}