#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <type_traits>
#include <sstream>
#include <boost/serialization/export.hpp>

#define DerivedAgent  Agent
#define DerivedAction Action

namespace Scavenger {
    struct DerivedAction;
    struct DerivedAgent;
}

namespace Base {
    struct Agent {
        virtual ~Agent() {}
        template<class Archive>
            void serialize(Archive & ar, unsigned) {
                ar.template register_type<Scavenger::DerivedAgent>();
            }
    };
}

namespace Base {
    struct Action {
        virtual ~Action() {}
        template<class Archive>
            void serialize(Archive& ar, unsigned) {
                boost::serialization::void_cast_register<Scavenger::DerivedAction, Action>();
                ar.template register_type<Scavenger::DerivedAction>();
            }
    };
}

namespace Scavenger {
    struct DerivedAction : ::Base::Action {
        template<class Archive>
            void serialization(Archive & ar, unsigned) {
                ar & boost::serialization::base_object<::Base::Action>(*this);
            }
    };
}

namespace Scavenger {
    struct DerivedAgent : ::Base::Agent {
        ::Base::Action* lastAction = nullptr; // Essentially I have added only this and..

        template<class Archive>
            void serialize(Archive & ar, unsigned) {
                ar & boost::serialization::base_object<::Base::Agent>(*this);
                ar & lastAction; // I added this to the .h files
            }
    };
}

BOOST_CLASS_EXPORT(::Base::Agent)
BOOST_CLASS_EXPORT(::Base::Action)
BOOST_CLASS_EXPORT(::Scavenger::DerivedAgent)
BOOST_CLASS_EXPORT(::Scavenger::DerivedAction)

int main()
{
    std::ostringstream oss;
    {
        boost::archive::text_oarchive oa(oss);

        auto scavenger = boost::make_shared<Scavenger::DerivedAgent>();
        scavenger->lastAction = new ::Scavenger::DerivedAction;

        boost::shared_ptr<::Base::Agent> obj = scavenger;
        oa << obj;
    }

    std::cout << oss.str() << "\n";

    {
        std::istringstream iss(oss.str());
        boost::archive::text_iarchive ia(iss);

        boost::shared_ptr<::Base::Agent> deserialized;
        ia >> deserialized;

        std::cout << "Typeid: " << typeid(*deserialized).name() << "\n";
        if (auto s = dynamic_cast<::Scavenger::DerivedAgent*>(&*deserialized))
            std::cout << "Typeid: " << typeid(*s->lastAction).name() << "\n";
    }
}
