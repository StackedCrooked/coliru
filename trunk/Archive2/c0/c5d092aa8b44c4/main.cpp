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

struct Reader {
    template <typename T>
    Packet readPacket(T const* data, size_t size) const {
        static_assert(boost::is_pod<T>::value     , "T must be POD");
        static_assert(boost::is_integral<T>::value, "T must be integral");
        static_assert(sizeof(T) == sizeof(char)   , "T must be byte-sized");

        bio::stream<bio::array_source> stream(bio::array_source(data, size));
        bar::text_iarchive ia(stream);
        Packet result;
        ia >> result;

        return result;
    }

    template <typename T, size_t N>
    Packet readPacket(T (&arr)[N]) const {
        return readPacket(arr, N);
    }

    template <typename T>
    Packet readPacket(std::vector<T> const& v) const {
        return readPacket(v.data(), v.size());
    }

    template <typename T, size_t N>
    Packet readPacket(boost::array<T, N> const& a) const {
        return readPacket(a.data(), a.size());
    }
};

template <typename MutableBuffer>
void make_packet(Packet const& data, MutableBuffer& buf)
{
    bio::stream<bio::array_sink> s(buf.data(), buf.size());
    bar::text_oarchive ar(s);

    ar << data;
}

int main() {
    boost::array<char, 1024> arr;

    for (int i = 0; i < 100; ++i) {
        make_packet(Packet { i }, arr);

        Packet roundtrip = Reader().readPacket(arr);
        assert(roundtrip.i == i);
    }
}
