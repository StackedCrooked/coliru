#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class Foo
{
public:
    Foo() : myInt(0) {}
    int myInt;
};

void myDeleter(Foo* iFoo)
{
    delete iFoo;
    std::cout << "deleted the foo." << std::endl;
}

typedef boost::shared_ptr<Foo> tFooPtr;

int main()
{
    tFooPtr myFooPtr(new Foo, myDeleter);
    std::cout << "made a foo. it's int is " << myFooPtr->myInt << std::endl;
    std::cout << "that's the end of main." << std::endl;
}
