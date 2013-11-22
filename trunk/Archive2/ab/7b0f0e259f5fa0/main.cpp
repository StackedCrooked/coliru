#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <iostream>

struct Test
{
    Test() : a(1), b(2) {}
    
    template<typename Archive>
    void serialize(Archive& ar, unsigned) const
    {
        ar & a & b;
    }
    int a, b;
};


int main()
{
    boost::archive::text_oarchive ar(std::cout);
    Test test;
    ar << test;    
}