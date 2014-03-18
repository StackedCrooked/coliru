#include <iostream>
#include <sstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

int main()
{
    std::ostringstream oss;
    boost::archive::binary_oarchive oa(oss);

    std::vector<char> v(1000);

    // stream
    oa << v;

    std::cout << "The number of bytes taken for the vector in an archive is " << oss.str().size() << "\n";
}
