/* Private Constructor : Used to restrict the creation of the objectof the particular class.
It prevents Inheritance
It can be used to create only one object across the application means SINGLETON
If you want to create object of the class that have private constructor than create object inside static fucntion
*/

#include<iostream>
class name
{
    private:
    name(){
        std::cout << "private constructuor is called " << std::endl;
        }
    public:
    static name* get();
};

name* name::get()
{
    name *local = new name();
    return local;
}


int main()
{
    name *obj;
    obj = name::get();
}