#include <iostream>

int main( int, char** )
{
    using namespace std;
    
    // The lambda function is what appears on the right side of the equals
    // sign, but the type of "fn" is called a closure. Important to remember
    // what a closure is.
    auto fn1 = []{};
    
    // We can call it like a regular function:
    fn1();
    
    // The stuff between the curly braces is the function body. We can put
    // anything in the body that we could put in the body of a normal function:
    // This is the same syntax, just split across multiple lines:
    auto fn2 = []
    {
        cout << "You called the lambda function via a closure object!" << endl;
    };
    
    // It get's evaluated, just like a normal function!
    fn2();
    
    return 0;
}
