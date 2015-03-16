#include <iostream>

int main(){ 
    char input, output;
    std::cin >> input;
    if (input != 'a' && input != 'e' && input != 'i' && input != 'o' && input != 'u')
    {
        if ('a' <= input && input <= 'c')   { output = 'a'; }
        else if (input <= 'g')              { output = 'e'; }
        else if (input <= 'l')              { output = 'i'; }
        else if (input <= 'r')              { output = 'o'; }
        else if (input <= 'z')              { output = 'u'; }
    }
}
