#include <iostream>
 
int main()
{
    char word[] = "hello";
    switch (word) {
        case "hello": std::cout << "hello";
        default: std::cout << "default";
    }
 
    std::cout << '\n';
}