#include <functional>   // for std::bind
#include <memory>       // for std::unique_ptr
#include <utility>      // for std::move
#include <iostream>     // printing

void showPtr(const char* name, const std::unique_ptr<int>& ptr)
{
    std::cout << "&" << name << " = " << &ptr << ", " << name << ".get() = "
              << ptr.get();
    if (ptr)
        std::cout << ", *" << name << " = " << *ptr;
    std::cout << std::endl;
}

int main()
{
    std::unique_ptr<int> myPointer(new int{42});
    showPtr("myPointer", myPointer);
    std::cout << "Creating lambda\n";
    auto lambda = std::bind([](std::unique_ptr<int>& myPointerArg){
        showPtr("myPointerArg", myPointerArg);
        *myPointerArg = 56;
        showPtr("myPointerArg", myPointerArg);
    }, std::move(myPointer));
    showPtr("myPointer", myPointer);
    lambda();
}
