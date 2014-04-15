#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <sstream>
#include <boost/archive/text_iarchive.hpp>

namespace mydata
{
    struct MyInfo 
    {
        std::string info = "extra info";

        MyInfo(std::string info = "") : info(std::move(info)) {}

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive &ar, const unsigned int /*version*/)
            {
                ar & info;
            }
    };

    struct MyData
    {
        std::string name;
        std::string type;
        boost::shared_ptr<MyInfo> myref;

        private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive &ar, const unsigned int /*version*/)
            {
                ar & name;
                ar & type;
                ar & myref;
            }
    };
}

int main()
{
    using namespace mydata;

    std::ostringstream oss;
    {
        MyData data { "this is a name", "this is a type", boost::make_shared<MyInfo>("this is info") };

        boost::archive::text_oarchive oa(oss);
        oa << data;
    }

    MyData cloned;
    std::istringstream iss(oss.str());
    {
        boost::archive::text_iarchive ia(iss);
        ia >> cloned;
    }

    // check equality
    {
        std::ostringstream oss2;

        boost::archive::text_oarchive oa(oss2);
        oa << cloned;

        std::cout << oss.str()  << "\n";
        std::cout << oss2.str() << "\n";
    }
}
