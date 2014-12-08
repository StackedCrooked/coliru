#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> values(20);
    std::iota(std::begin(values), std::end(values), -6);
    
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(std::begin(values), std::end(values), g);

   for (auto& element : values) {
       std::cout << element << std::endl;
   }
   
   return 0;
}