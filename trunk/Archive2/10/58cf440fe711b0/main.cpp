#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

class gps_position
{
        public:
        int i ;
        int j;
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int /*version*/)
        {
                ar & i;
                ar & j;
        }

        gps_position(){};
        gps_position(int a, int b):i(a), j(b){};
};

int main()
{
   std::stringstream ss;
   boost::archive::text_oarchive ar( ss );
   gps_position obj(10, 20);
   ar << obj;
}
