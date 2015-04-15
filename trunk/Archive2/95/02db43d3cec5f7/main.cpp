#include <iostream>

int main(){
    int array[1];
    int count = 0;
    for(;count < 5000;count++){
        int *mem = &array[count];
        std::cout<<"Location: "<<mem<<std::endl;
        std::cout<<"Value: "<<*mem<<std::endl<<std::endl;
        
         }
    
    
    
    
    return 0;
}