#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <cassert>

typedef boost::function<int()>            IntFunc0;
typedef boost::function<int(int)>         IntFunc1;
typedef boost::function<int(int,int)>     IntFunc2;
typedef boost::function<int(int,int,int)> IntFunc3;

int foo0()            { return 0; }
int foo1(int)         { return 1; }
int foo2(int,int)     { return 2; }
int foo3(int,int,int) { return 3; }

int main()
{
    IntFunc0 func0;
    IntFunc1 func1;
    IntFunc2 func2;
    IntFunc3 func3;

    // "straight" assignment ok:
    // -------------------------
    func0 = foo0;                          assert (0 == func0());
    func1 = foo1;                          assert (1 == func1(-1));
    func2 = foo2;                          assert (2 == func2(-1,-1));
    func3 = foo3;                          assert (3 == func3(-1,-1,-1));

    // "mixed" assignment not ok:
    // --------------------------
    // func0 = foo1;                       // compile error
    // func3 = foo2;                       // compile error
    // func1 = func2;                      // compile error, just the same
    // func2 = func1;                      // compile error, just the same
    
    // SOLUTION: you can always rebind:
    // --------------------------------
    func0 = boost::bind(foo3, 1, 2, 3);    assert (func0() == 3);
    func3 = boost::bind(foo1, _3);         assert (func3(-1,-1,-1) == 1);
    func3 = boost::bind(foo2, _3, _2);     assert (func3(-1,-1,-1) == 2);
    // same arity, reversed arguments:
    func3 = boost::bind(foo3, _3, _2, _1); assert (func3(-1,-1,-1) == 3);

    // can't bind more than number of formal parameters in signature:
    // --------------------------------------------------------------
    // func3 = boost::bind(foo1, _4);      // in fact, the bind is fine, but assigning to `func3` fails
}
