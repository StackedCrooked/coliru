#include <boost/utility/result_of.hpp>
#include <typeinfo>
#include <iostream>
#include <ostream>

using namespace std;

struct PolymorphicFunctionObject
{
    template<typename T> struct result;

    template<typename Arg>
    struct result< PolymorphicFunctionObject(Arg) >
    {
        typedef Arg type;
    };

    template<typename Arg1,typename Arg2>
    struct result< PolymorphicFunctionObject(Arg1,Arg2) >
    {
        typedef Arg2 type;
    };

    template<typename Arg>
    Arg operator()(Arg t) const
    {
        return t;
    }

    template<typename Arg1,typename Arg2>
    Arg2 operator()(Arg1 t1,Arg2 t2) const
    {
        return t2;
    }
};

int main()
{
    cout << typeid
    (
        PolymorphicFunctionObject::result< PolymorphicFunctionObject(int) >::type
    ).name() << endl;
    // Output is - int

    cout << typeid
    (
        PolymorphicFunctionObject::result< PolymorphicFunctionObject(char,double) >::type
    ).name() << endl;
    // Output is - double

    // -----------------
    // Or using boost::result_of, which queries ::result internally:

    cout << typeid
    (
        boost::result_of< PolymorphicFunctionObject(short) >::type
    ).name() << endl;
    // Output is - short

    cout << typeid
    (
        boost::result_of< PolymorphicFunctionObject(char,float) >::type
    ).name() << endl;
    // Output is - float

    // ------------------
    // Or using C++11 decltype:
    cout << typeid
    (
        decltype( PolymorphicFunctionObject()( long() ) )
    ).name() << endl;
    // Output is - long

    cout << typeid
    (
        decltype( PolymorphicFunctionObject()( long(),unsigned() ) )
    ).name() << endl;
    // Output is - unsigned int

}