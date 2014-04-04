#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

namespace X { namespace Y {

    struct my_type {
        std::string a;
        double b;

    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, unsigned) {
            ar & a;
            ar & b;
        }

    public:
        my_type(){}
        virtual ~my_type(){}
    };


    namespace Z
    {
        typedef unsigned int my_time;
        typedef std::string data_type;
    }

} }

#include <iostream>

int main()
{
    boost::archive::text_oarchive oa(std::cout);
    X::Y::my_type a;
    a.a = "in my_type";
    a.b = 3.14;
    X::Y::Z::my_time b = 42;
    X::Y::Z::data_type c = "hello world";

    oa << a << b << c;
}
