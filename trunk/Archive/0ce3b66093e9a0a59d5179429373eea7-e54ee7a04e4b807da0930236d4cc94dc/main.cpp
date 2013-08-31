#include <atomic>
#include <thread>
#include <iostream>
#include <string>

int main()
{
    std::atomic<std::string> atomicString;

    atomicString.store( "TestString1" );

    std::cout << atomicString.load() << std::endl;

    atomicString.store( "TestString2" );

    std::cout << atomicString.load() << std::endl;

    return 0;
}
