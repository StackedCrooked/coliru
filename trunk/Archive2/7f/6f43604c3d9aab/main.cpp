/* Destructor: is a special function, which gets called when object is out of scope. and destructor is used to avoid memory leaks
*/

#include<iostream>
class name
{
    public:
    name(){std::cout << " default constructor" << std::endl; }
    ~name(){std::cout<< "Default Destructor" << std::endl;}
};

int main()
{
    name obj;
}