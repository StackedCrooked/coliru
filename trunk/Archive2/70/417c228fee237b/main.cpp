#include <iostream>
#include <new>

using namespace std;

template <typename T>
class SmartWrapper
{
    private:
    T * obj;
    public:
    SmartWrapper(T * newObj)
    {
        cout << "Wrapper: Begin" << endl;
        obj = newObj;
    }
    ~SmartWrapper()
    {
        delete obj;
        cout << "Wrapper: End" << endl;
    }
};

class Person
{
    public:
    Person()
    {
        cout << "Person: Begin" << endl;
    }
    ~Person()
    {
        cout << "Person: End" << endl;
    }
};

class Dog
{
    public:
    Dog()
    {
        cout << "Dog: Begin" << endl;
    }
    ~Dog()
    {
        cout << "Dog: End" << endl;
    }
};

int main()
{
    // we should have the same number of begins and ends.
    // we actually have half of ends because objects created
    // without smart pointers are not deleted after each iteration.
    for(int i = 0; i < 2; i++)
    {
        Dog* c1 = new Dog();
        Person* c2 = new Person();
        SmartWrapper<Dog> s1(new Dog());
        SmartWrapper<Person> s2(new Person());
    }
   
   return 0;
}
