#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::stack<std::string> myStack;
    myStack.push("strings");
    myStack.push("few");
    myStack.push("a");
    
    while(!myStack.empty())
    {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }
    
    return 0;
}