#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


int main()
{
    char *a = "hello";
    char *b = new char[strlen(a) + 1](0);
    std::copy(a, a + strlen(a), b);
   
}