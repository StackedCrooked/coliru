#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>

struct Information {
    int x;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version){ ar & x; }
};

std::ostream& operator<<(std::ostream& out, Information const& info){
    return out << info.x;
}

struct Sample {
    mutable Information* f;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version){ ar & f; }
};

std::ostream& operator<<(std::ostream& out, Sample const& sample){
    if(sample.f){
        out << *sample.f;
    } else {
        out << "<no info>";
    }
    return out;
}

struct Data {
    std::vector<Sample> samples;
    template <typename Archive> void serialize(Archive& ar, const unsigned int version){ ar & samples; }
};

std::ostream& operator<<(std::ostream& out, Data const& data){
    for(auto&& sample : data.samples){
        out << sample << " ";
    }
    return out;
}

int main()
{
    Data d;
    for(unsigned int i = 0; i < 100; ++i){
        Sample s; s.f = new Information;
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
