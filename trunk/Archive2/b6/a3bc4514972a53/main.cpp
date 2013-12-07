#include <iostream>
#include <string>

// The C++ standard library provides a class template called std::function, and
// can be used to store any callable object. Here's its header:
#include <functional>

void my_function()
{
    std::cout << "Hello, people!" << std::endl;
}

void my_other_function()
{
    std::cout << "Hello, person!" << std::endl;
}

int main( int, char** )
{
    using namespace std;
    
    // The declaration looks a little funny. It's just like a class template like
    // std::vector. Instead of putting in the type it holds, we pass in the function
    // signature for the template parameter.
    //
    // In this case, the function returns void and takes no arguments. It's
    // signature looks like this (The empty parens indicate no parameters):
    //
    // void()
    //
    // A function that returns int and takes a std::string looks like this:
    //
    // int(std::string)
    // 
    // What kind of function is this?
    //
    // std::string(int, double, std::string)
    
    // Here's a function object:
    std::function<void()> fn = my_function;
    
    // We can call it, just like a function!
    fn();
    
    // Unlike a closure, we can reassign a std::function
    fn = my_other_function;
    
    // New function!
    fn();
    
    // Here's the magic. We can assign the std::function to a closure object.
    // The resulting closure will be stored away in the std::function
    fn = []{ cout << "Hello, lambda!" << endl; };
    
    // Call dat lambda!
    fn();
    
    return 0;
}
