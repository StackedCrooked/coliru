#include <iostream>
#include <memory>
#include <string>
 
typedef std::shared_ptr<int> IntPtr;
 
void output(const std::string& msg, int* pInt)
{
    std::cout << msg << *pInt << "\n";
}
 
int main()
{
    int* pInt = new int(42);
    IntPtr pShared(new int(42));
 
    output("Naked pointer ", pInt);
    // output("Shared pointer ", pShared); // compiler error
    output("Shared pointer with get() ", pShared.get());
 
    delete pInt;
}