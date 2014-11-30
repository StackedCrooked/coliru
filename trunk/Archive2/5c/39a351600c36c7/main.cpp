#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/assume_abstract.hpp>

struct Derived;

struct Base
{
    int x;
    Base() { x = 0; }
    virtual ~Base() {}

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar.template register_type<Derived>();
        ar & x;
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Base)

struct Derived : Base
{
    int y;
    Derived() { x = 1; y = 2; }
    virtual ~Derived() {}

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Base>(*this);
        ar & y;
    }
};

int main()
{
    std::stringstream ss;

    {
        Derived derived;
        Base *basePtr = &derived;

        boost::archive::binary_oarchive oa(ss);
        oa.register_type<Derived>();

        oa << basePtr;
        ss.flush();
    }

    {
        boost::archive::binary_iarchive ia(ss);
        ia.register_type<Derived>();

        Base *basePtr = nullptr;

        ia >> basePtr;
        std::cout << "basePtr->x = " << basePtr->x << "\n";
        if (Derived* derivedPtr = dynamic_cast<Derived*>(basePtr))
            std::cout << "derivedPtr->y = " << derivedPtr->y << "\n";
    }
}
