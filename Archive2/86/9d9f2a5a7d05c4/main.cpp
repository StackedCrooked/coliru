#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class ClassA
{
 public:
    int number;
    char name[64];
};

namespace boost { namespace serialization {

template<typename Archive>
void serialize(Archive & ar, ClassA& g, const unsigned int )
{
        ar & g.number;
        ar & g.name;
}

} }

int main(int argc, char* argv[])
{
        ClassA obj1;
        obj1.number = 21;
        snprintf(obj1.name, sizeof ClassA::name, "%s", "Hello World!");

        std::ofstream ofs("efg.txt", std::ios::out);
        if (!ofs.fail())
        {
            boost::archive::text_oarchive oa(ofs);
            oa << obj1;
        }

        ClassA obj2;
        std::ifstream ifs("efg.txt");
        if (!ifs.fail())
        {
            boost::archive::text_iarchive ia(ifs);
            ia >> obj2;

        }
        std::cout << "obj2 = {" << obj2.number << ", " << obj2.name << "}\n";
}
