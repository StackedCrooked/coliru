#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

int data = 42;

template <typename Ar>
void some_output(std::ostream& os)
{
    Ar ar(os);
    std::cout << "Writing archive at " << os.tellp() << "\n";
    ar << BOOST_SERIALIZATION_NVP(data);
}

template <typename Ar>
void roundtrip(std::istream& is)
{
    data = -1;
    std::cout << "Reading archive at " << is.tellg() << "\n";
    Ar ar(is);
    ar >> BOOST_SERIALIZATION_NVP(data);
    assert(data == 42);
}

#include <sstream>

int main()
{
    std::stringstream ss;

    //some_output<boost::archive::text_oarchive>(ss); // this derails the binary archive that follows
    some_output<boost::archive::binary_oarchive>(ss);
    some_output<boost::archive::xml_oarchive>(ss);
    some_output<boost::archive::text_oarchive>(ss);

    //roundtrip<boost::archive::text_iarchive>(ss);
    roundtrip<boost::archive::binary_iarchive>(ss);
    roundtrip<boost::archive::xml_iarchive>(ss);
    roundtrip<boost::archive::text_iarchive>(ss);

    // just to prove that there's remaining whitespace
    std::cout << "remaining: ";
    char ch;
    while (ss>>std::noskipws>>ch)
        std::cout << " " << std::showbase << std::hex << ((int)(ch));
    std::cout << "\n";

    // of course, anything else will fail:
    try {
        roundtrip<boost::archive::text_iarchive>(ss);
    } catch(boost::archive::archive_exception const& e)
    {
        std::cout << "Can't deserialize from a stream a EOF: " << e.what();
    }
}
