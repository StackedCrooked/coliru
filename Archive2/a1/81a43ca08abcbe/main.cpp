#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/smart_ptr/make_shared.hpp>

namespace mydata
{
    struct MyInfo 
    {
        std::string info = "extra info";

        MyInfo(std::string info) : info(std::move(info)) {}

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
    MyData data { "this is a name", "this is a type", boost::make_shared<MyInfo>("this is info") };

    boost::archive::text_oarchive oa(std::cout);
    oa << data;
}
