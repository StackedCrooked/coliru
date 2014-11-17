#include <iostream>
#include <thread>

int f()
{
    static int i = 0;
    i++;
    return i;
}    
int b = f();

int main()
{
 f();
 std::cout << b;

}
