#include <boost/serialization/serialization.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/variant.hpp>
#include <sstream>

using PolyArchive = boost::variant<
            boost::archive::polymorphic_oarchive&,
            boost::archive::polymorphic_iarchive&
        >;

struct /*abstract*/ ISerializable {
    virtual void serialize(PolyArchive, unsigned) = 0;
};

struct MyClass : ISerializable {
    std::string data_member = "Morgana"; // something to serialize

    // the one method we need to implement
    virtual void serialize(PolyArchive ar, unsigned) override;
};

int main()
{
    std::stringstream ss;
    {
        // serialize:
        boost::archive::polymorphic_text_oarchive outpu(ss);

        MyClass object;
        outpu << object;

    }

    // Debug dump;
    std::cout << "Serialized: " << ss.str();

    {
        // read back:
        boost::archive::polymorphic_text_iarchive input(ss);

        MyClass cloned;
        input >> cloned;

        std::cout << "Roundtripped: ";
        boost::archive::polymorphic_text_oarchive pta(std::cout);
        pta << cloned;
    }
}

////////////////////////////////
// implementation:

namespace /*detail*/ {
    template <typename F> struct wrap_visitor : boost::static_visitor<> {

        wrap_visitor(F f) : f_(f) { }

        template<typename... T> void operator()(T&&... t) const {
            f_(std::forward<T>(t)...);
        }

    private:
        F f_;
    };

    template <typename F> 
    wrap_visitor<F> make_visitor(F f) {
        return std::move(f);
    }
}

void MyClass::serialize(PolyArchive ar, unsigned) {

    boost::apply_visitor(make_visitor([=](auto& ar) { 
            ar & data_member;
        }), ar);
}
