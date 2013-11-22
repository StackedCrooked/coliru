#include <iostream>

enum class Type : int
{
    A, B
};


int main()
{
    Type type = Type::A;
    int& n = static_cast<int&>(type);
}