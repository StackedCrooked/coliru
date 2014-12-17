#include <cstring>
#include <iostream>

using namespace std;

int main() 
{
    char input[100] = "A bird came down the walk";
    char *token = strtok(input, " ");
    while (token != '\0') {
        cout << token << '\n';
        token = strtok('\0', " ");
    }
}