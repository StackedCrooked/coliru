#include <iostream>
#include <string>
#include <vector>

int ar[] = 
{ 0, 2, 4, 3, 4, 4,
  1, 0, 2, 4, 6, 9,
  3, 4, 1, 3, 0, 1};

int main (){
    
    size_t counter = 0;
    
    for (auto a : ar){
        if (a){
            std::cout << a << "," ;
            counter++;
        }
    }
    std::cout << "\n\nsize: " << counter << std::endl;
 
 return 0;
}