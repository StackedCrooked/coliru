#include <ctime>
#include <iostream>
 
int main()
{
    std::time_t result = std::time(NULL);
    std::cout<<"hello"<<std::endl;
    std::cout << std::asctime(std::localtime(&result))
              << result << " seconds since the Epoch\n";

}