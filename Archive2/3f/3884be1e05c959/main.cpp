#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

struct FooDerived;

struct Foo {
    virtual ~Foo() = default;

    template<class Archive>
        void serialize(Archive& ar, unsigned) {
            //// Uncommenting the next line is a workaround?
            // boost::serialization::void_cast_register<FooDerived, Foo>();
            ar.template register_type<FooDerived>();
        }
};

struct FooDerived : Foo {
    template<class Archive>
        void serialization(Archive & ar, unsigned) {
            ar & boost::serialization::base_object<Foo>(*this);
        }
};

BOOST_CLASS_EXPORT(Foo)
BOOST_CLASS_EXPORT(FooDerived)

int main()
{
    boost::archive::text_oarchive oa(std::cout);

    Foo* obj = new FooDerived;
    oa & obj; // archive_exception what(): unregistered void cast N9Scavenger6ActionE<-N4Base6ActionE
}
