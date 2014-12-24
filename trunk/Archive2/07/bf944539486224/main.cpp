#include <iostream>

enum A{ x = -2, y = 2 };

A a = 2; // cannot initialize a variable of type 'A' with an rvalue of type 'int'
A b = 3; // cannot initialize a variable of type 'A' with an rvalue of type 'int'

int main(){ }