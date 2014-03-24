#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/rational.hpp>
#include <iostream>

namespace boost { namespace serialization {

    template <typename Archive, typename T>
        void save(Archive& ar, ::boost::rational<T> const& r, unsigned /*version*/)
        {
            int n = r.numerator(), d = r.denominator();
            ar & boost::serialization::make_nvp("numerator", n);
            ar & boost::serialization::make_nvp("denominator", d);
        }

    template <typename Archive, typename T>
        void load(Archive& ar, ::boost::rational<T>& r, unsigned /*version*/)
        {
            int n, d;
            ar & boost::serialization::make_nvp("numerator", n);
            ar & boost::serialization::make_nvp("denominator", d);

            r = ::boost::rational<T>(n, d);
        }

} }

BOOST_SERIALIZATION_SPLIT_FREE(boost::rational<int>);

using namespace boost;
#include <iostream>
#include <sstream>

int main()
{
    rational<int> number(2, 3), other;

    std::stringstream ss;
    {
        archive::xml_oarchive oa(ss);
        oa << serialization::make_nvp("rational", number);
    }

    std::cout << "Serialized: '" << ss.str() << "'\n";

    {
        archive::xml_iarchive ia(ss);
        ia >> serialization::make_nvp("rational", other);
    }

    std::cout << "Deserialized: " << other;
}
