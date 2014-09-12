#include <cstring>
#include <iostream>
 
int main() 
{
    char input[100] = "A bird came down the walk";
    char *token = std::strtok(input, " ");
    while (token != NULL) {
        std::cout << token << '\n';
        token = std::strtok(NULL, " ");
    }
}