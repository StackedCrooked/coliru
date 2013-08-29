#include <iostream>

template< typename T >
void invert (T*start, T*end){
    T buff;
    while(start < end){
        buff = *start;
        *start = *end;
        *end = buff;
        end--;
        start++;
    }
}

int main(){
    
    int arr[8] = {1,2,3,4,5,6,7,8};
    //
    std::cout<<"before"<<std::endl;
    for(int i = 0; i < 8; i++)
        std::cout<<arr[i]<<std::endl;
    
    invert<int> (arr, arr+7);
    
    std::cout<<"after"<<std::endl;
    for(int i = 0; i < 8; i++)
        std::cout<<arr[i]<<std::endl;
    
    std::cout<<"WORK";
}
