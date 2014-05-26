#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include <sstream>

class SerializableSmth 
{
    public:
    void init() {
        for  (int i=0; i<100; ++i) {
            data.push_back("Some fairly long string " + std::to_string(i) + " with a number");
        }
    }
    friend class boost::serialization::access;

    std::list<std::string> data;
    template<class Archive> void serialize(Archive & ar, unsigned int version)
    {
        ar & data;
    }
};

BOOST_CLASS_VERSION(SerializableSmth, 1);

#include <iostream>

int main()
{
    std::string serialized;
    {
        std::stringstream ss;
        boost::archive::text_oarchive oa(ss);

        SerializableSmth original;
        original.init();

        oa << original;

        serialized = ss.str();
    }

    {
        boost::iostreams::basic_array_source<char> as(serialized.data(), serialized.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > is(as);

        // now let's see it back:
        boost::archive::text_iarchive ia(is);

        SerializableSmth cloned;
        ia >> cloned;
        std::cout << "Cloned data has " << cloned.data.size() << " records\n";
    }
}
