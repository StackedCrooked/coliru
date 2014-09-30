#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/rational_adaptor.hpp>
#include <iostream>

namespace boost { namespace serialization {

    template <typename Archive>
        void save(Archive& ar, ::boost::multiprecision::backends::gmp_rational const& r, unsigned /*version*/)
        {
            std::string tmp = r.str(10000, std::ios::fixed);
            ar & tmp;
        }

    template <typename Archive>
        void load(Archive& ar, ::boost::multiprecision::backends::gmp_rational& r, unsigned /*version*/)
        {
            std::string tmp;
            ar & tmp;
            r = tmp.c_str();
        }

} }

BOOST_SERIALIZATION_SPLIT_FREE(::boost::multiprecision::backends::gmp_rational)

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/array.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <map>

template <class T>
class A {
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & a;
        }

  public:
    T a;
    bool operator<(A const& o) const { return a<o.a; }
};

#include <sstream>

using KeyElement = boost::multiprecision::mpq_rational;
using Key        = A<boost::array<KeyElement,2> >;
using Data       = std::map<Key, int>;

int main()
{
    std::stringstream ss;
    {
        Data mmm { 
            { Key {{{KeyElement { 1, 2 }, KeyElement { 3, 4 }} }}, 5 }, 
            { Key {{{KeyElement { 6, 7 }, KeyElement { 8, 9 }} }}, 42 },
        };
        boost::archive::text_oarchive oa(ss);

        oa << mmm;
    }

    std::cout << "Serialized:\t" << ss.str() << "\n";

    {
        boost::archive::text_iarchive iarch(ss);
        Data mmm; 
        iarch >> mmm;

        std::cout << "Roundtrip:\t";
        boost::archive::text_oarchive oa(std::cout);
        oa << mmm;
    }
}

