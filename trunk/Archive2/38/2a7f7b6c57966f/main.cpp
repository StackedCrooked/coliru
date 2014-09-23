#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

namespace spacename {

struct Information {
    int x;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version){ ar & x; }
};

std::ostream& operator<<(std::ostream& out, Information const& info){
    return out << info.x;
}

template <typename T>
struct Sample {
    mutable Information* f;
    std::vector<T> data;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version){ ar & f; }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Sample<T> const& sample){
    if(sample.f){
        out << *sample.f;
    } else {
        out << "<no info>";
    }
    return out;
}

struct Data {
    std::vector<Sample<float>> samples;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version){ ar & samples; }
};

std::ostream& operator<<(std::ostream& out, Data const& data){
    for(auto&& sample : data.samples){
        out << sample << " ";
    }
    return out;
}

}

namespace boost { namespace serialization {
    template <typename T>
    struct version<spacename::Sample<T>> {
        using type = mpl::int_<1>;
        using tag = mpl::integral_c_tag;
        static constexpr auto value = version::type::value;
    };
}}

int main()
{
    using namespace spacename;
    Data d;
    for(unsigned int i = 0; i < 100; ++i){
        Sample<float> s; s.f = new Information; s.data = {1, 2, 3, 4};
        d.samples.emplace_back(std::move(s));
    }
    
    std::stringstream stream;
    boost::archive::text_oarchive oar(stream);
    oar << d;
    
    Data b;
    boost::archive::text_iarchive iar(stream);
    iar >> b;
    
    std::cout << "Before: " << d << std::endl;
    std::cout << "After : " << b << std::endl;
}
