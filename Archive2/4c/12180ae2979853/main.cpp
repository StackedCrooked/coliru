#include <iostream>
#include <vector>

int ar[] = 
{ 0, 2, 4, 3, 4, 4,
  1, 0, 2, 4, 6, 9,
  3, 4, 1, 3, 0, 1};

int main (){
    
    std::vector<int> b;
    for (auto a : ar){
        if (a){
            std::cout << a << "," ;
            b.push_back(a);
        }
    }
    std::cout << "\n\nsize: " << b.size() << std::endl;
 
 return 0;
}