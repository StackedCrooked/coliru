#include <future>
#include <iostream>

int main()
{
    auto f1 = std::async(std::launch::async, []{ std::cout << "Hello";  });
    auto f2 = std::async(std::launch::async, []{ std::cout << " ";      });
    auto f3 = std::async(std::launch::async, []{ std::cout << "World!"; });
    
    f1.get(), f2.get(), f3.get();
}
