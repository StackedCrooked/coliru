#include <iostream>
#include <thread>

void hello()
{
    std::cout << "hello concurrent world\n";
}

int main(int argc, char* argv[])
{
    std::thread th(hello);
    th.join();
    return 0;
}