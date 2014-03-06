#include <iostream>
#include <string>

const std::string array[] = "123";

int main(void)
{
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); ++i) {
        std::cout << i << ": " << array[i] << std::endl;
    }
    return 0;
}