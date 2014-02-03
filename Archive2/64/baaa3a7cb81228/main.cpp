#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

template<typename T>
class shared_type
{
    shared_ptr<T>   m_value;
    public:
    shared_type(T value): m_value(make_shared<T>(value)){}
    shared_type(shared_ptr<T> ptr): m_value(ptr){cout << "pointer constructor"<<endl;}
    shared_type(shared_type<T> & object): m_value(*object.m_value){ cout << "copy constructor"<<endl;}
    
    shared_type<T> & operator =(T value)
    {
        *m_value = value;
        return *this;
    }
    
    operator T() const  // cast operator overload
    {
        return *m_value;
    }
    
    operator shared_ptr<T>() const
    {
        return m_value;
    }
    
    virtual ~shared_type(){}
};

int main()
{
    shared_type<int>    myint(10);
    shared_ptr<int>     mysharedint = myint;
    shared_type<int>    myint2(mysharedint);

    int a = myint;
    
    cout << "*myint="<<myint<<endl;
    cout << "a="<<a<<endl;
    cout << "*mysharedint="<<*mysharedint<<endl;
    cout << "*myint2="<<myint2<<endl;
    
    myint = 20;
    cout <<endl;
    cout << "*myint="<<myint<<endl;
    cout << "a="<<a<<endl;
    cout << "*mysharedint="<<*mysharedint<<endl;
    cout << "*myint2="<<myint2<<endl;
    

}