#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>
#include <ostream>
using namespace boost;
using namespace std;

struct Data
{
    double value;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & value;
    }
};

int main()
{
    Data d={3.1415926};
    char buffer[256];
    {
        iostreams::array_sink sink(buffer);
        iostreams::stream<iostreams::array_sink> stream(sink);
        archive::binary_oarchive out_archive(stream);
        out_archive << d;
    }
    Data restored = {0.0};
    {
        iostreams::array_source source(buffer);
        iostreams::stream<iostreams::array_source> stream(source);
        archive::binary_iarchive in_archive(stream);
        in_archive >> restored;
    }
    cout << boolalpha << ( restored.value == d.value ) << endl;
}
