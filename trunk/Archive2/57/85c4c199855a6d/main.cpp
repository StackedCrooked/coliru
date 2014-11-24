#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

struct I1
{
    I1() {}
    virtual ~I1() {}

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }
};

struct C1 : I1
{
    virtual ~C1() {}

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<I1>(*this);
    }
};

struct I2
{
    virtual ~I2() {}

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & p;
    }

    boost::shared_ptr<I1> p;
};

struct C2 : I2
{
    C2() { p = boost::shared_ptr<I1>(new C1); }
    virtual ~C2() { }

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<I2>(*this);
    }

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(I1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(I2)

int main()
{
    C2 c2;

    std::string s;
    std::stringstream ss(s);

    boost::archive::text_oarchive oa(ss);
    oa.register_type<I1>();
    oa.register_type<C1>();
    oa.register_type<I2>();
    oa.register_type<C2>();

    oa << c2;

    std::cout << ss.str();

    boost::archive::text_iarchive ia(ss);
    ia.register_type<I1>();
    ia.register_type<C1>();
    ia.register_type<I2>();
    ia.register_type<C2>();

    ia >> c2;

    assert(dynamic_cast<C1*>(c2.p.get()));
}
