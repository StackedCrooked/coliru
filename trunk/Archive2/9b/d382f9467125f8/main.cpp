#include <iostream>
#include <thread>
int a;
int b = f();
int f()
{
    a++;
    return 2;
}    
int main()
{
 a++;
 std::cout << b;

}
