#include <iostream>       
#include <thread>         

int main() 
{
    int value = 10;

    std::thread th {[](int x){std::cout << x<< "\n";}, value};     

    th.join();
}
