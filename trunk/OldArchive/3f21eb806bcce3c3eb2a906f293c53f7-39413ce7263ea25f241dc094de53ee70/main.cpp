#include <iostream>
 
template <typename X>
void func (X x)
{
    std::cout << x.x << "\n";
}
 
int main ()
{
    func((struct {int x;}){1});
}