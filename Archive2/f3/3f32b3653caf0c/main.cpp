#include <vector>
#include <iostream>

int main() {
    
    std::vector<std::vector<double>> vec(35, std::vector<double>(88));
    vec[34][87] = 3.14159;
    std::cout << vec[34][87] << std::endl;
}