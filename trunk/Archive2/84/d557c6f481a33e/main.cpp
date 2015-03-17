#include <iostream>

enum A{} t;                 // enum A{} is a complete type (OK)
enum class B:int z;         // enum class B:int is not a complete type

int main()
{
    
}