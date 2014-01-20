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
            degrees(d), minutes(m), seconds(s){}
};

int main() {
    // create and open a character archive for output
    {
        std::string outFileName = "testOut.xml";
        std::ofstream ofs(outFileName);

        // create class instance
        const gps_position g(35, 59, 24.567f);

        // save data to archive
        {
            boost::archive::xml_oarchive oa(ofs);
            // write class instance to archive
            oa << BOOST_SERIALIZATION_NVP(g);
        }
    }

    // read
    {
        std::string inFileName = "testOut.xml";
        std::ifstream ifs(inFileName);

        {
            boost::archive::xml_iarchive ia(ifs);
            // write class instance to archive
            gps_position g;
            ia >> BOOST_SERIALIZATION_NVP(g);
        }
    }
}
