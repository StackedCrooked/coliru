#include <iostream>
using namespace std;

//First Step - Adds Text

int main()
{
    // Program Code goes here.

    cout <<  "Hello. You have attempted to access the Variable Database." << endl;
    cout <<  "Here are the Variables: " << endl;

    char letter;    letter = 'X';
    int number;     number = 169;
    float decimal = 6.9;
    double pi = 3.14159;
    bool isTrue = true;

    cout << "char letter: " << letter << endl;
    cout << "int number: " << number << endl;
    cout << "float decimal: " << decimal << endl;
    cout << "double pi: " << pi << endl;
    cout << "bool isTrue: " << isTrue << endl;


    return 0;
}
