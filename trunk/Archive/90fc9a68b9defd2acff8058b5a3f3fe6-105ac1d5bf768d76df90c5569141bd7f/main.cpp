#include <iostream>
#include <ctime>

int main(){
   std::time_t result = std::time(NULL);
   const std::tm* t =  std::localtime(&result);
   if(t->tm_wday == 1 and t->tm_mday < 7)
    std::cout << "true" << std::endl;
    else
    std::cout << "false" << std::endl;
}
