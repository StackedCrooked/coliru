#include <iostream>

// test0: unqualified lookup inside the inner namespace
namespace outer
{
    void function0() { std::cout << "outer::function" << std::endl; }
    
    namespace inner
    {
        void test0()
        {
            function0(); // finds outer::function
        }
    }
}


// test1: stopping unqualified lookup from finding global functions
namespace outer
{
    struct X {};
}
void function1(outer::X) { std::cout << "::function1" << std::endl; }

namespace another_outer
{
    void function1(outer::X) { std::cout << "another_outer::function1" << std::endl; }
}

namespace outer
{
    namespace inner
    {
        void function1(outer::X) { std::cout << "outer::inner::function1" << std::endl; }
    }
    
    void test1()
    {
        X x;
        function1(x); // finds ::function1
        
        {
            using namespace inner;
            function1(x); // finds (only) outer::inner::function1
        }
        
        {
            using namespace another_outer;
            //function1(x); // finds both ::function1 and another_outer::function1
            // error: ambiguous call
        }
    }
}


// test2: ADL
namespace outer
{
    struct ADL {};
    void function2(ADL) { std::cout << "outer::function2" << std::endl; }
}

int main()
{
    outer::inner::test0();
    outer::test1();
    
    outer::ADL x;
    function2(x); // finds outer::function2
}

