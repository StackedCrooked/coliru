#include "MessageServer.h"
#include <thread>


int main()
{
    std::thread t([](){ MessageServer server(9999); });
    std::cout << "OK" << std::endl;
}