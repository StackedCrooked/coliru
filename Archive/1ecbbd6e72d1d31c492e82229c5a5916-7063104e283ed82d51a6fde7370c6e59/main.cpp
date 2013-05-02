#include "thread"
#include "iostream"
#include "exception"

void teste()
{
    std::cout << "Funcionou Itmr" << std::endl;
}

int main()
{
    std::thread t(teste);
    t.join();
    return 0;
}