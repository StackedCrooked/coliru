#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp> 
#include <boost/serialization/optional.hpp> 
#include <boost/serialization/map.hpp> 
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

namespace A
{
    typedef std::map<std::string, std::string> parameter_strings;
    struct FullData 
    {
        FullData() : pincode(0) {}
        FullData(const parameter_strings & parms) : pincode(0), detail(parms) {}

        virtual ~FullData() {}

        std::string country;
        int pincode;

      private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive &ar, unsigned int)
            {      
                ar & country;
                ar & pincode;
            } 

         parameter_strings detail;

      public:
         typedef std::list<FullData> FullDataInfo; // what should be done to serialize this data 
    };

}

// SimpleData.cpp
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_IMPLEMENT(A::FullData)
BOOST_CLASS_IMPLEMENTATION(A::FullData    , boost::serialization::object_serializable)
BOOST_CLASS_TRACKING(A::FullData          , boost::serialization::track_never)

int main()
{
    boost::archive::text_oarchive oa(std::cout);

    A::FullData data1({ { "key1", "value1" }, { "key2", "value2" } });
    data1.pincode = 1234;
    data1.country = "ES";
    A::FullData data2({ { "key3", "value3" }, { "key4", "value4" } });
    data2.pincode = 4321;
    data2.country = "UK";

    A::FullData::FullDataInfo list { data1, data2 };

    oa << list;
}
