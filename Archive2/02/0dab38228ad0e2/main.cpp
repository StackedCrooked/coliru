// for different output formats
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

// for the data structures
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/map.hpp>

struct X
{
    int p;
    double q;
  private: 
    friend boost::serialization::access;
    template <typename Ar>
        void serialize(Ar& ar, unsigned) {
            ar & BOOST_SERIALIZATION_NVP(p);
            ar & BOOST_SERIALIZATION_NVP(q);
        }
};

struct Y
{
    float m;
    double n;
  private: 
    friend boost::serialization::access;
    template <typename Ar>
        void serialize(Ar& ar, unsigned) {
            ar & BOOST_SERIALIZATION_NVP(m);
            ar & BOOST_SERIALIZATION_NVP(n);
        }
};

struct Z
{
   std::map<std::string, boost::shared_ptr<X>> Xtype;
   std::map<std::string, boost::shared_ptr<Y>> Ytype; 

   int i;
   std::string name; 
  private: 
    friend boost::serialization::access;
    template <typename Ar>
        void serialize(Ar& ar, unsigned) {
            ar & BOOST_SERIALIZATION_NVP(i);
            ar & BOOST_SERIALIZATION_NVP(name);
            ar & BOOST_SERIALIZATION_NVP(Xtype);
            ar & BOOST_SERIALIZATION_NVP(Ytype);
        }
};

#include <boost/random.hpp> // for test data
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <algorithm>

Z const& fixture()
{
    static Z const z = [] {
        Z z;

        boost::random::mt19937 engine;
        auto fgen = boost::bind(boost::random::uniform_real_distribution<float>(), engine);
        auto dgen = boost::bind(boost::random::uniform_real_distribution<double>(), engine);
        auto cgen = boost::bind(boost::random::uniform_int_distribution<char>('a', 'z'), engine);
        auto igen = boost::bind(boost::random::uniform_int_distribution<int>(), engine);

        auto sgen = [&] (int maxlen) { std::string s; std::generate_n(back_inserter(s), igen() % maxlen, cgen); return s; };

        std::generate_n(inserter(z.Ytype, z.Ytype.end()), 1000, [&] { 
                auto py = boost::make_shared<Y>(); 
                py->m = fgen();
                py->n = dgen();
                return std::make_pair(sgen(32), py);
                });
        std::generate_n(inserter(z.Xtype, z.Xtype.end()), 3000, [&] { 
                auto px = boost::make_shared<X>(); 
                px->p = igen();
                px->q = dgen();
                return std::make_pair(sgen(32), px);
                });

        z.i    = igen();
        z.name = sgen(8);

        return z; 
    }();
    return z;
}

#include <nonius/main.h++>
#include <sstream>

NONIUS_BENCHMARK("text archive", [](nonius::chronometer meter) {
    auto const& z = fixture();
    meter.measure([&](int /*i*/) { 
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);
        oa << z;

        Z clone;
        boost::archive::text_iarchive ia(ss);
        ia >> clone;

        return ss.str().size(); // something observable to thwart the overly smart optimizer
    });
})

NONIUS_BENCHMARK("binary archive", [](nonius::chronometer meter) {
    auto const& z = fixture();
    meter.measure([&](int /*i*/) { 
        std::stringstream ss;
        boost::archive::binary_oarchive oa(ss);
        oa << z;

        Z clone;
        boost::archive::binary_iarchive ia(ss);
        ia >> clone;

        return ss.str().size(); // something observable to thwart the overly smart optimizer
    });
})

NONIUS_BENCHMARK("xml archive", [](nonius::chronometer meter) {
    auto const& z = fixture();
    meter.measure([&](int /*i*/) { 
        std::stringstream ss;
        boost::archive::xml_oarchive oa(ss);
        oa << boost::serialization::make_nvp("root", z);

        Z clone;
        boost::archive::xml_iarchive ia(ss);
        ia >> boost::serialization::make_nvp("root", clone);

        return ss.str().size(); // something observable to thwart the overly smart optimizer
    });
})
