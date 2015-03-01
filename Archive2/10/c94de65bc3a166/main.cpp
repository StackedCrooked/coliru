#include <iostream>
 
int main()
{
    int i = 2;
    switch (i) {
        case 1: std::cout << "1";
        case 2: std::cout << "2";   //execution starts at this case label
        case 3: std::cout << "3";
        case 4:
        case 5: std::cout << "45";
                break;              //execution of subsequent statements is terminated
        case 6: std::cout << "6";
    }
 
    std::cout << '\n';
 
    switch (i) {
        case 4: std::cout << "a";
        default: std::cout << "d"; //there are no applicable constant_expressions
                                   //therefore default_statement is executed
    }
 
    std::cout << '\n';
 
    switch (i) {
        case 4: std::cout << "a";  //nothing is executed
    }
}