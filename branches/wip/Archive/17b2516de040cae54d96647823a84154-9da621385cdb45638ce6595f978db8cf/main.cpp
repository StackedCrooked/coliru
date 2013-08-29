#include <iostream>

struct Object
{
    Object() {}
    Object(const Object& other) {std::cout << this << ":Object(const Object& " << &other <<" )\n";}
    Object(Object&& other) {std::cout << this << ":Object(Object&& " << &other <<" )\n";}

    Object& makeChanges() { std::cout << this <<":makeChanges()\n"; return *this;}
};

#define PROCESS 5

#if PROCESS == 1

Object
process(Object arg)
{
    return arg.makeChanges();
}

#elif PROCESS == 2

Object
process(const Object& arg)
{
    return Object(arg).makeChanges();
}

Object
process(Object&& arg)
{
    return std::move(arg.makeChanges());
}

#elif PROCESS == 3

Object
process(const Object& arg)
{
    Object retObj = arg;
    retObj.makeChanges();
    return retObj; 
}

Object
process(Object&& arg)
{
    return std::move(arg.makeChanges());
}

#elif PROCESS == 4

Object
process(Object arg)
{
    return std::move(arg.makeChanges());
}

#elif PROCESS == 5

Object
process(Object arg)
{
    //arg.makeChanges();
    return arg;
}

#endif

Object source(Object obj) {return obj;}
Object source() {return Object();}

int main()
{
    std::cout << "process lvalue:\n";
    Object x;
    Object t{process(x)};
    std::cout << "\nprocess xvalue:\n";
    Object u{process(std::move(x))};
    std::cout << "\nprocess prvalue:\n";
    Object v{process(source(source()))};
    (void)t;
    (void)u;
    (void)v;
}