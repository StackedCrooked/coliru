#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/optional.hpp>
#include <fstream>

class MyClass {

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(my_member);
    }

    boost::optional<int> my_member = 42;
};

int main() {
    boost::archive::xml_oarchive oa(std::cout);
    MyClass const g;
    oa << boost::serialization::make_nvp("root", g);
}
