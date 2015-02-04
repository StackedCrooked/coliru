#include <iostream>
 
int main()
{
    char word[] = "hello";
    int i = 2;
    switch (word) {
        case "hello": std::cout << "hello";
        default: std::cout << "default";
    }
 
    std::cout << '\n';
}