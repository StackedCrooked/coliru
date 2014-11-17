#include <iostream>
#include <thread>
int a;
int b = a++;
int main()
{
 a++;
 std::cout << b;

}
