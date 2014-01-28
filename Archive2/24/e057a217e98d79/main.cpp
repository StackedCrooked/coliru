#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include <stack>
using namespace std;

int main()
{
    stack <char> stackA;
    stack <char> stackB;
    stack <char> stackC;

    char avariable;
    cout << "Enter a string: ";
    avariable = cin.get();
    while(avariable != '\n')
    {
        if(avariable != ' ')
        {

            stackA.push(avariable);
            stackB.push(avariable);
            avariable = cin.get();
        }}

    stackC.push('$');

    while(!stackB.empty())
    {
        avariable = stackB.top(); //error, cannot resolve overloaded function 'top' based on conversion to type 'char'
        stackC.push(avariable);
        stackB.pop(); //statement cannot resolve address of overloaded function
    }

    avariable = '$';
    stackC.push('$');

    while(!stackA.empty())
    {
        if(avariable == stackC.top()) //invalid operands of type 'char' and <unresolved overloaded function type>' to binary 'operator=='
        {
            avariable = stackA.top(); //cannot resolve overloaded function 'top' based on conversion to type 'char'
            stackA.pop(); //cannot resolve address of overloaded function 
            stackC.pop(); //cannot resolve address of overloaded function 
        }
        else
        {
            cout << "The string of characters entered is not a palindrome." << endl;
        }
    }

    if (stackC.top() == '$') //invalid operands of type 'char' and <unresolved overloaded function type>' to binary 'operator=='
    {
        cout <<"The string of characters entered is a palindrome." << endl;
    }

}