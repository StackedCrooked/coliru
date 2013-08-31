#include <iostream>
#include <vector>

int main()
{
    auto my_vector_bool = std::vector<bool> { false };
    
    auto b1 = my_vector_bool.back(); // to capture the proxy
    b1 = true; // write into my_vector_bool
    
    std::cout << b1 << "\n";
 
    auto my_vector_int = std::vector<int> { false };
 
    auto i1 = my_vector_int.back(); // No proxy
    //i1 = true; // NOT write into my_vector_int}
    
    std::cout << i1 << "\n";
}