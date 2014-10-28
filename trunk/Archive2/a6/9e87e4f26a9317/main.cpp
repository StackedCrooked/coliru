#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <iostream>
#include <fstream>
#include <boost/serialization/string.hpp>
#include <string>

class A {
    friend class boost::serialization::access;

  public:
    std::string a;
    virtual ~A() {}

  private:
    template <class Archive>
    void serialize(Archive &archive, const unsigned int version)
    {
        archive &BOOST_SERIALIZATION_NVP(a);
    }
};

class B : public A {
    friend class boost::serialization::access;

  public:
    std::string b;

  private:
    template <class Archive>
    void serialize(Archive &archive, const unsigned int version)
    {
        using namespace boost::serialization;
        archive &make_nvp("base", base_object<A>(*this));
        archive &BOOST_SERIALIZATION_NVP(b);
    }
};

BOOST_CLASS_EXPORT(B)

void save()
{
    std::ofstream file("archive.xml", std::ios::binary);
    boost::archive::xml_oarchive oa(file);
    B *myB = new B();
    myB->a = "1";
    myB->b = "2";

    A* myA = myB;
    oa << boost::serialization::make_nvp("myA", myA);
    delete myB;
    file.close();
}

void load()
{
    std::ifstream file("archive.xml", std::ios::binary);
    boost::archive::xml_iarchive ia(file);
    A *myA;

    ia >> boost::serialization::make_nvp("myA", myA);
    
    std::cout << "a: " << myA->a << std::endl;
    if (B* myB = dynamic_cast<B*>(myA))
        std::cout << "b: " << myB->b << std::endl;
}

int main()
{
    save();
    load();
}
