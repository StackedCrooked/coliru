#include <iostream>
#include <string>
#include <vector>

// Note the return by reference:
std::string& myname()
{
    std::string name = "Colby";
    return name; // We're returning a reference to a variable on the stack!
};

int main()
{
    // We grab a reference from the function.
    // But beware. It's a reference... in dead stack space!
    auto& name = myname();
    
    // Now let's try to modify it... What will happen?
    name = "Hi";
    
    return 0;
}
