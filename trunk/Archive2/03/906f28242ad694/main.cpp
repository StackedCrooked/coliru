#include <iostream>
#include <memory>
 
template<typename T>
using Shared = std::shared_ptr<T>;
 
int main() {
    Shared<int> mySharedInt = std::make_shared<int>(10);
    std::cout << *mySharedInt << std::endl;
 
    return 0;
}