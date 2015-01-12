#include <iostream>
#include <memory>
#include <thread>

int main()
{
    std::unique_ptr<std::thread> threadPtr;
    threadPtr.reset(std::make_unique<std::thread>([&]
    {
      //...
    
    }).release());

}
