#include <iostream>
#include <unordered_map>


struct A
{
    A():
      jo(1)
    {}
    
    int jo;
};


int main()
{
    typedef std::pair< A*, unsigned > ConstraintKey;
    typedef std::unordered_map<ConstraintKey, int > RangeConstraintContainer;
    
    RangeConstraintContainer test;
}
