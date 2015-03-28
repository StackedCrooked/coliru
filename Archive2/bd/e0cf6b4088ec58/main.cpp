/* Constructor : special Function same name as Class name, which gets called only when object gets created. */

#include<iostream>
class name
{
    public:    // Member functions should be in Public section, Only initialized data will be in private section.
    name(){
        std::cout << "constructuor is called " << std::endl;
        }
    name(int a)
    {
        std::cout << "parameterized constructor " << a << std::endl;
    }
};

int main()
{
    name obj;
    name obj1(1);
}