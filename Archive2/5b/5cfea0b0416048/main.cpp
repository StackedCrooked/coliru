/* Pure Virtual Function: We define function prototype in base class and implementation is in derived class
-> the class which contains this is called Abstract class(base class)
-> derived class must override this pure virtual fucntion
*/

#include<iostream>
class base
{
public:
    virtual void show()=0;
};
class derived : public base
{
public:
    void show()
    {
        std:: cout << " I am a pure virtual fucntion" << std:: endl;
    }
};
int main()
{
    base *a;;// = new derived;
    derived b;
    a=&b;
    a->show();
}
