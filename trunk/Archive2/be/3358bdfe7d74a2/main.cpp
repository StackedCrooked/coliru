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

namespace Reader {
    template <typename T>
    Packet deserialize(T const* data, size_t size) {
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
    Packet deserialize(T (&arr)[N]) {
        return deserialize(arr, N);
    }

    template <typename T>
    Packet deserialize(std::vector<T> const& v) {
        return deserialize(v.data(), v.size());
    }

    template <typename T, size_t N>
    Packet deserialize(boost::array<T, N> const& a) {
        return deserialize(a.data(), a.size());
    }
}

template <typename MutableBuffer>
void serialize(Packet const& data, MutableBuffer& buf)
{
    bio::stream<bio::array_sink> s(buf.data(), buf.size());
    bar::text_oarchive ar(s);

    ar << data;
}

int main() {
    boost::array<char, 1024> arr;

    for (int i = 0; i < 100; ++i) {
        serialize(Packet { i }, arr);

        Packet roundtrip = Reader::deserialize(arr);
        assert(roundtrip.i == i);
    }
    std::cout << "Done\n";
}
