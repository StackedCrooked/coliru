#include <iostream>

namespace bill {
    const char * null ="EMPTY";
    const int MAX_STACK_SIZE = 100;
    class myStackClass {
    private:
        int i;
    public:
        myStackClass();
        myStackClass(int[], int);
        int peek();
        int pop();
        int push(int insertMe);
        const char empty[5];
    };
}

using namespace bill;
bill::myStackClass::myStackClass()
    : i(0), empty{1,2,3,4,5}
{}

bill::myStackClass::myStackClass(int[],int)
    : i(0), empty{1,2,3,4,5}
{}

int bill::myStackClass::peek()
{
    return 0;
}

int main()
{
    bill::myStackClass foo;
}
