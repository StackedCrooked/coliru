#include <iostream>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{

    std::cout << "test\n";

    std::string test = "test";

    if (test == argv[1]) {
        std::cout << "a test";
    }


}