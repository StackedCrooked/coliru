#include <vector>
#include <iostream>

std::vector<char> f()
{
    char const arr [] = "ASDF";
    return {arr, arr+sizeof(arr)}; // include null terminator
}

int main() {std::cout << f().data();}