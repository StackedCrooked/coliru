#include <stdio.h>
#include <string.h>
#include <iostream>
#include <type_traits>

int main(){
    auto  a = new float[10][20][30];
    
    if (std::is_same<decltype(a), float(*)[20][30]>{})
        std::cout << "jrok was right!";
}
