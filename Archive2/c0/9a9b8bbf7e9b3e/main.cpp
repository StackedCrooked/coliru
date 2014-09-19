#include <algorithm>
#include <vector>

struct B
{
};

struct A
{
    A(){}
    
    #if 1
    A(const B& b)
    {
        // constructor converting B into A
    }
    #endif
};

A toA(const B& b)
{
    A rc;
    //free function converting B into A
    return rc;
}


int main()
{
    std::vector<A> VecA;
    B* arrayB;
    size_t elementsOfB;
    
    //here fill array B and elmentsOfB in C legacy code - does not matter for minimum example

    //now copy array of B into vector of A
    std::copy(arrayB, arrayB + elementsOfB, std::back_inserter(VecA));
  
    return 0;
}
