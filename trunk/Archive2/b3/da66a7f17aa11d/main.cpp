#include <iostream>
namespace x86_JaguarCPU
{
class x86_Jaguar
{
public:
x86_Jaguar()
{
cout << "Hello from Jaguar!";
}
~x86_Jaguar()
{
cout << "Goodbye from Jaguar!";
}
}
}
using namespace x86_JaguarCPU;
int main()
{
x86_Jaguar JAGUARCPU;
JAGUARCPU::x86_Jaguar();
}