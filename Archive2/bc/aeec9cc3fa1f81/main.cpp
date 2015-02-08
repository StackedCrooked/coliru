#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <sstream>

namespace bar = boost::archive;
namespace bio = boost::iostreams;

struct Packet {
    int i;
    template <typename Ar> void serialize(Ar& ar, unsigned) { ar & i; }
};

Packet deserialize(std::istream& is) {
    bar::text_iarchive ia(is);
    Packet result;
    ia >> result;
    return result;
}

void serialize(Packet const& data, std::ostream& os)
{
    bar::text_oarchive ar(os);
    ar << data;
}

int main() {
    std::stringstream ss;

    for (int i = 0; i < 100; ++i) {
        serialize(Packet { i }, ss);

        Packet roundtrip = deserialize(ss);
        assert(roundtrip.i == i);
    }
    std::cout << "Done\n";
}
