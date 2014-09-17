#include <iostream>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/function.hpp>

using namespace std;

using namespace boost;

struct Proto
{
    typedef shared_ptr<Proto> Ptr;
    
    virtual ~Proto()
    {
        
    }
};

struct A : public Proto
{
    typedef shared_ptr<A> Ptr;
    struct State
    {
        int a;
        int b;
        bool c;
    };
    State state;
    
    virtual ~A()
    {
        
    }
};

template<typename Type, typename FieldPtr, typename ValueType >
struct SetProperty
{
    SetProperty(FieldPtr Type::State::*fieldPtr, ValueType value)
    :   fieldPtr_(fieldPtr), 
         value_(value)
    {
        cout<<"SetProperty: Functor created"<<endl;
    }
    
    bool operator()(Proto::Ptr ptr)
    {
        shared_ptr<Type> casted = dynamic_pointer_cast<Type>(ptr);
        if(ptr)
        {
            cout<<"SetProperty: operator(): initial value:"<< (casted->state.*fieldPtr_) <<endl;
            casted->state.*fieldPtr_ = value_;
            cout<<"SetProperty: operator(): actual value:"<< (casted->state.*fieldPtr_) <<endl;
        }
    }
    
    FieldPtr Type::State::* fieldPtr_;
    ValueType value_;
};

typedef boost::function<bool (Proto::Ptr)> SetFunc;

template<typename Type>
struct SetPropertyWrapper
{
    template<typename FieldPtr, typename ValueType >
    SetPropertyWrapper(FieldPtr Type::State::*fieldPtr, ValueType value)
    {
        cout<<"SetPropertyWrapper: Creating Functor"<<endl;
        setProperty_ = SetProperty<Type, FieldPtr, ValueType>(fieldPtr, value);
    }

    operator SetFunc()
    {
        cout<<"SetPropertyWrapper: Casting Wrapper to Functor"<<endl;
        return setProperty_;
    }
    
    SetFunc setProperty_;
};




int main()
{
   cout << "Hello World" << endl;
   A obj;
   A::Ptr objPtr (new A);
   
   SetFunc func = SetPropertyWrapper<A>(&A::State::a, 2);
   func(objPtr);
   
   return 0;
}
