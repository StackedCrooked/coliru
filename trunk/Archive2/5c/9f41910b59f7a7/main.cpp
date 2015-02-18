#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>


unsigned int reverse_imp1(unsigned int number)
{
  unsigned int reversed = 0;
  do
  {
      reversed = reversed*10 + number%10;
      number = number/10;
  }while(number != 0);
  return reversed;
}



unsigned int reverse(unsigned int number)
{
std::chrono::time_point<std::chrono::system_clock> start, end;
start = std::chrono::system_clock::now();
unsigned int result = reverse_imp1(number);
end = std::chrono::system_clock::now();
std::chrono::duration<long signed int, std::nano> elapsed_seconds = end-start;
std::cout << "Reversed number calculated in: " << elapsed_seconds.count() << std::endl;;
return result;
}


int main()
{
    unsigned int number = 1234567;
    std::cout << "Number:" << number << ", Reverse:" << reverse(number) << std::endl;
}
