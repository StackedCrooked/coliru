// #include "SimpleData.hpp" BEGIN

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp> 
#include <boost/serialization/optional.hpp> 
#include <boost/serialization/map.hpp> 
#include <boost/serialization/shared_ptr.hpp>

namespace A
{
    typedef std::map<std::string, std::string> parameter_strings;
    struct Name
    {
        std::string firstname;
        std::string lastname;

        template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                ar & firstname;
                ar & lastname;
            } 
    };

    struct Address
    {
        std::string street;
        std::string city;

        template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                ar & street;
                ar & city;
            } 

    };

    struct FullData 
    {
        FullData();
        FullData(const parameter_strings & parms);

        virtual ~FullData();

        boost::optional<Name> nameinfo;       // instance of struct Name
        boost::optional<Address> addressinfo; // instance of struct Address
        parameter_strings detail;

        std::string country;
        int pincode;

        private :
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive &ar, const unsigned int version)
            {
                ar & nameinfo;       // are these enough to take of serialization of Name and 
                ar & addressinfo;   // Address
                ar & country;
                ar & pincode;
                ar & detail;
            } 
    };

}

// #include "SimpleData.hpp" END
#include <boost/serialization/export.hpp>

namespace A
{
    FullData::FullData()
    {

    }

    FullData::~FullData()
    {

    }

    FullData::FullData(const parameter_strings & parms): detail(parms)
    {

        // impelmentation
    }

}

#include <boost/archive/text_oarchive.hpp>

BOOST_CLASS_EXPORT_IMPLEMENT(A::FullData)
BOOST_CLASS_IMPLEMENTATION(A::FullData    , boost::serialization::object_serializable)
BOOST_CLASS_TRACKING(A::FullData          , boost::serialization::track_never)

int main()
{
    A::FullData data({ { "key1", "value1" }, { "key2" , "value2" } });
    data.nameinfo    = A::Name    { "firstname", "lastname" };
    data.addressinfo = A::Address { "street", "city" };
    data.pincode     = 99977;
    data.country     = "Gibraltar";

    boost::archive::text_oarchive oa(std::cout);
    oa << data;
}
