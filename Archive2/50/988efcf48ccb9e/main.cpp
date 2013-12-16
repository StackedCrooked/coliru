#include <iostream>
#include <string>
#include <functional>

// We can return closure objects if we wrap them up in a std::function
std::function<void()> get_function()
{
    return []{ std::cout << "Hello from a closure!" << std::endl; };
}

// Here's where capture by reference can cause trouble...
std::function<void()> get_other_function()
{
    int value = 9;
    // Lambda captures "value" by reference. We return the closure object
    // wrapped in a std::function, but that closure still has a reference to
    // a stack variable. Oh nose!
    return [&]{ std::cout << "Value from closure is " << value << std::endl; };
}

int main( int, char** )
{
    using namespace std;
    
    // Grab that function!
    auto fn = get_function();
    
    // Call it!
    fn();
    
    // Get that other function
    fn = get_other_function();
    
    // What'll happen?
    fn();
    
    return 0;
}
