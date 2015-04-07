#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>
#include <sstream>

using boost::serialization::make_binary_object;

enum class Example : uint8_t {
    First  = 1,
    Second = 2,
};

int main() {

    std::stringstream stream;
    boost::archive::binary_oarchive ar(stream, boost::archive::no_header);

    auto data = Example::First;
    ar << make_binary_object(&data, sizeof(data));

    std::cout << "Size: " << stream.str().size() << "\n";
}
