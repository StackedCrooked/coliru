#include <iostream>
using namespace std;
 
char f(...);
 
template <typename T>
struct A
{
enum { value = sizeof(f(T())) };
};
 
double f(int);
 
 
int main()
{
std::cout << A<int>::value << std::endl;
}