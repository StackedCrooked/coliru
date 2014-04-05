#include <iostream>
#include <string>
#include <vector>

void function_test(char arr[10]) {
    std::cout << "Trying to get array size inside function: " << sizeof(arr) <<std::endl;
}

int main()
{
    char testing[32];
    
    std::cout << "Trying to get array size: " << sizeof(testing) << std::endl;
    
    function_test(testing);
    
    std::cout << "The size of a pointer: " << sizeof(char *) << std::endl;
}
