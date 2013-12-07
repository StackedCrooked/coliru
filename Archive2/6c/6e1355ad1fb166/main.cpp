#include <iostream>
#include <string>
#include <vector>

auto my_function(int* x){
    std::cout << x;
}

int main()
{
    int myNum = 5;
    my_function(myNum);
}