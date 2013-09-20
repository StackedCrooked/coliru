#include <iostream>

enum TMyEnum
{
    Enum_1, Enum_2, Enum_3, 
    Enum_4, Another_Enum, 
    Enum_count
};
    
int main() {
    std::cout << TMyEnum::Enum_count << std::endl;   
}
