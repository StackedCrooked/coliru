#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using iarchive = boost::archive::text_iarchive;
using oarchive = boost::archive::text_oarchive;

class Base
{
public:
    virtual void print() const = 0;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};

class Derived : public Base
{
public:
    void print() const { std::cout << "Derived" << std::endl; }
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Base>(*this);
    }
};

int main()
{
    std::vector<Base*> bases = {new Derived()};
    std::stringstream ss;
    oarchive ostream(ss);
    ostream.register_type<Derived>();
    ostream << bases;
    
    std::vector<Base*> loaded;
    iarchive istream(ss);
    istream.register_type<Derived>();
    istream >> loaded;
    for (Base* p : loaded) p->print();
}