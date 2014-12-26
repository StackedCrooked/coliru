#include <boost/serialization/serialization.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/make_shared.hpp>
#include <sstream>

class Interface {
    public:
        virtual void aVirtual() = 0;
        virtual ~Interface() {}
    private:
        friend class boost::serialization::access;
        template<class Archive> void serialize(Archive&, unsigned) { }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Interface)

template<class T>
class Derived : public Interface {
    public:
        Derived(T in = 0) : m_data(in) {}
        virtual void aVirtual() { /*Do something*/ }
        T const& getData() const { return m_data; }
    private:
        T m_data;
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive& ar, unsigned)
            {
                ar & boost::serialization::base_object<Interface>(*this);
                //// alternatively, if you don't want to make the abstract base serializable:
                // boost::serialization::void_cast_register<Derived, Interface>();

                ar & m_data;
            }
};

BOOST_CLASS_EXPORT(Derived<std::string>)
BOOST_CLASS_EXPORT(Derived<double>)
BOOST_CLASS_EXPORT(Derived<int>)

int main()
{
    typedef boost::shared_ptr<Interface> ItfPtr;
    std::stringstream ss;

    {
        boost::archive::text_oarchive oa(ss);
        ItfPtr o = boost::make_shared<Derived<int> >(42);

        oa << o;
    }

    std::cout << "Serialized: '" << ss.str() << "'\n";

    {
        boost::archive::text_iarchive ia(ss);

        ItfPtr o;
        ia >> o;

        if (auto p = boost::dynamic_pointer_cast<Derived<int> >(o))
            std::cout << "Deserialized into Derived<int> with data: " << p->getData() << "\n";
    }
}
