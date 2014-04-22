#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp> 
#include <boost/serialization/optional.hpp> 
#include <boost/serialization/list.hpp> 
#include <boost/serialization/shared_ptr.hpp>
#include <list>

    namespace Input { namespace EMMA {

    struct Node
    {
        std::string firstname;
        std::string lastname;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar & firstname;
            ar & lastname;
        }

    };

    struct Nodes : public std::list<Node>
    {
        std::string address;
        std::string country;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar & boost::serialization::base_object<std::list<Node> >(*this);
            ar & address;
            ar & country;
        }

    };

    } }

    BOOST_CLASS_EXPORT_KEY(Input::EMMA::Node);
    BOOST_CLASS_EXPORT_KEY(Input::EMMA::Nodes);

    BOOST_CLASS_EXPORT_IMPLEMENT(Input::EMMA::Nodes);
    BOOST_CLASS_IMPLEMENTATION(Input::EMMA::Nodes    , boost::serialization::object_serializable);
    BOOST_CLASS_TRACKING(Input::EMMA::Nodes          , boost::serialization::track_never);

    int main()
    {
        boost::archive::text_oarchive oa(std::cout);
        using namespace Input::EMMA;
        Nodes nodes;
        nodes.address = "Mr.";
        nodes.country = "Puerto Mazarique";
        nodes.insert(nodes.end(), Node{"John", "Doe"});
        nodes.insert(nodes.end(), Node{"Jane", "Greenwalt"});
        nodes.insert(nodes.end(), Node{"Morgan", "Cheese"});
        nodes.insert(nodes.end(), Node{"Walton", "Whiz"});

        oa << nodes;
    }
