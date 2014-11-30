#include <iostream>
#include <string>
int foo() { return 0; }
std::string foo() { return "0"; }

int main() { int a=foo(); }