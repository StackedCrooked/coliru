#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

 
int main() 
{
    char input[100] = "123 45 + 5 * 18 /";
    char *token = strtok(input, " ");
    while (token != NULL) {
        cout << token << endl;
        
        if(token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/'){
            int a= atoi(token);
            cout<< "int: " << a << endl;
        }
        token = std::strtok(NULL, " ");
    }
    cout << "input: " << input << endl;
}