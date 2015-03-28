/* Copy Constructor : By default compiler will provide a copy constructor this will work when you call A obj2=obj
*/
#include <iostream>

class A
{
    private:
    int i;
    public:
    A():i(0){}
    void set(int temp)
    {
        i = temp;
    }
    int get()
    {
        return i;
    }
};

int main()
{
    A obj;
    obj.set(2);
    A obj2 = obj;
    std::cout << obj2.get() << std::endl;
}