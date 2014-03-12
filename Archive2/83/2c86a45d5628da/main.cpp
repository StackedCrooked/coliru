#include <iostream>
#include <memory>
 
typedef std::shared_ptr<int> IntPtr;
 
void report(IntPtr ptr) 
{
    if (ptr) {
        std::cout << "*ptr=" << *ptr << "\n";
    } else {
        std::cout << "ptr is not a valid pointer.\n";
    }
}
 
int main()
{
    IntPtr ptr;
    report(ptr);
 
    ptr = IntPtr(new int(7));
//    report(ptr);
//    ptr.reset();
    report(ptr);
}
