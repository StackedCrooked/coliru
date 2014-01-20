
#include <fstream>
#include <string>

// include headers that implement a archive in simple text format
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
class gps_position
{
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(degrees);
        ar & BOOST_SERIALIZATION_NVP(minutes);
        ar & BOOST_SERIALIZATION_NVP(seconds);
    }
    int degrees;
    int minutes;
    float seconds;
public:
    gps_position(){};
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}
};

int main() {
    std::string outFileName = "testOut.xml";

    // create class instance
    const gps_position g(35, 59, 24.567f);

    // save data to archive
    {
        // create and open a character archive for output
        std::ofstream ofs(outFileName);
        boost::archive::xml_oarchive oa(ofs);
        // write class instance to archive
        oa << BOOST_SERIALIZATION_NVP(g);
        // archive and stream closed when destructors are called
    }

    // ... some time later restore the class instance to its orginal state
    gps_position newg;
    {
        // create and open an archive for input
        std::ifstream ifs(outFileName);
        boost::archive::xml_iarchive ia(ifs);
        // read class state from archive
        ia >> newg;
        // archive and stream closed when destructors are called
    }
    return 0;
}
