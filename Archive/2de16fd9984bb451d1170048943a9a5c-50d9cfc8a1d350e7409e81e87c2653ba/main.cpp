#include <iostream>
#include <vector>

int main()
{
    double elements[] = {1.5, 2.5, 3.8, 4.3, 5.1};
    std::vector<double> vec(elements, elements + 5);
    
    std::cout << vec[3] << std::endl;
    
    // but:
    //      std::cout << [3]vec << std::endl;
    // doesn't compile!!
    
        return 0;    
}