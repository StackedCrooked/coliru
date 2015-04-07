/* Static variable will declare the member varaible , we need ti explicitly define that variable*/

#include<iostream>

class A
{
    int x;
public:
    A()
    {
        std::cout << "A constrcutor called" << std::endl;
    }
};
class B
{
    static A a; // Only declaration takes place
public:
    B(){
    std::cout << "B constrcutor called" << std::endl;
    }
    static A getA() { return a; }
} ;
A  B::a; // Define the static member variable as out side
int main()
{
    B b1,b2,b3; // B Constrctor gets called 3 times coz 3 objects got created.
    A a = b1.getA(); // A Constructor gets called only one time coz A is a Static function which share the same memory for n objects.
}
