#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/serialization.hpp>

struct XString {
    std::string s;

    template <class Archive>
    void serialize(Archive &ar, unsigned int) {
        ar & s;
    }
};

struct WithPointers {
    WithPointers(const char* n = nullptr) {
        if (n) name = new XString ({ n });
    }

    WithPointers(WithPointers const&) = delete;
    WithPointers& operator=(WithPointers const&) = delete;

    ~WithPointers() { 
        delete name; 
    }

    XString* name = nullptr;

    template <class Archive>
    void serialize(Archive &ar, unsigned int) {
        ar & name;
    }
};

#include <iostream>
#include <sstream>

int main()
{
    std::string serialized; 

    typedef WithPointers Location;

    {
        Location l1("da name");
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);

        oa << l1;
        serialized = oss.str();
    }

    std::cout << "serialized: '" << serialized << "'\n";

    {
        Location l2;
        std::istringstream iss(serialized);
        boost::archive::text_iarchive ia(iss);

        ia >> l2;
        std::cout << "Deserialized as '" << l2.name->s << "'\n";
    }
}
