#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/make_shared.hpp>
#include <boost/phoenix.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <sstream>

#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>

#include <boost/random.hpp>

namespace detail
{
    struct add_to_archive_f 
    {
        template <typename, typename> struct result { typedef void type; };
        template <typename Archive, typename T> 
            void operator()(Archive& ar, T const& t) const {
                ar << BOOST_SERIALIZATION_NVP(t);
            }
    };

    static const boost::phoenix::function<add_to_archive_f> add_to_archive { };
    static auto const crand = boost::bind(boost::uniform_int<char>(),    boost::mt19937());
    static auto const drand = boost::bind(boost::uniform_real<double>(), boost::mt19937());
}

template <typename Archive = boost::archive::binary_oarchive, typename... Data>
size_t archive_size(Data const&... data)
{
    std::stringstream ss;
    Archive oa(ss);

    boost::fusion::for_each(boost::make_tuple(data...), 
            detail::add_to_archive(
                boost::phoenix::ref(oa), 
                boost::phoenix::arg_names::arg1
                ));

    std::vector<char> compressed;
    boost::iostreams::filtering_ostream fos;
    fos.push(boost::iostreams::bzip2_compressor());
    fos.push(boost::iostreams::back_inserter(compressed));

    boost::iostreams::copy(ss, fos);

    return compressed.size();
}

template <typename Archive = boost::archive::binary_oarchive, typename... Data>
void benchmark(Data const&... data)
{
    std::cout << __PRETTY_FUNCTION__ << ":\t" << archive_size<Archive>(data...) << "\n";
}

struct Base {
    boost::array<double, 1000> data;
    Base() { std::generate_n(data.begin(), data.size(), detail::drand); }
    virtual ~Base() {}

  private:
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, unsigned /*version*/) {
        ar & BOOST_SERIALIZATION_NVP(data);
    }
};

struct Derived : Base {
    std::string x;
    Derived() : Base(), x(1000, '\0') { std::generate_n(x.begin(), x.size(), detail::crand); }

  private:
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive& ar, unsigned /*version*/) {
        ar & boost::serialization::make_nvp("base", boost::serialization::base_object<Base>(*this));
        ar & BOOST_SERIALIZATION_NVP(x);
    }
};

template <typename Archive> 
void some_scenarios()
{
    std::vector<char> v(1000); 
    std::generate_n(v.begin(), v.size(), detail::crand);

    benchmark<Archive>(v);
    benchmark<Archive>(boost::make_shared<std::vector<char>>(v));
    benchmark<Archive>(3.14f, 42, 42ull, "hello world");
    benchmark<Archive>(boost::make_shared<Base>());
    benchmark<Archive>(boost::make_shared<Derived>());
}

int main()
{
    some_scenarios<boost::archive::binary_oarchive>();
    some_scenarios<boost::archive::text_oarchive>();
    some_scenarios<boost::archive::xml_oarchive>();
}
