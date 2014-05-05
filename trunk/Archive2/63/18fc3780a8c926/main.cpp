#include <thread>
#include <iostream>

using namespace std;

int main(){
    int i=1;
    
    for(int j=0;j<10;j++){
     i = (i-1)%5;
     cout << i << endl ;
        
    }   
    
    return 0;
}