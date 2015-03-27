#include<iostream>

class sally
{
private:
    int value;
public:
    sally():value(20){}
    friend void func(sally &obj);    //function prototype 
};
void func(sally &so)     // friend sunction ..... in friend function we can change the private member values.
{
    so.value = 100;
    std::cout << so.value <<std::endl;
}
int main()
{
    sally obj;
    func(obj);     // friend function call
}
