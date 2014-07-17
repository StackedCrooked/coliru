// This example shows how to initialize some maps
// Compile with this command:
//      clang++ -std=c++11 -stdlib=libc++ map_initialization.cpp -o map_initialization

#include <iostream>
#include <map>
#include <string>

std::size_t three() {
    return 3;
}

int main() 
{
    int i[three()];
    return 0;
}