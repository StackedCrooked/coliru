#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/make_shared.hpp>
#include <fstream>

class DerivedA;
class DerivedB;

class Base
{
    public:
        Base(void) = default;
        virtual ~Base() = default;

        virtual double func(void) const = 0;

    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar.template register_type<DerivedA>();
                ar.template register_type<DerivedB>();
            }
}; 

typedef boost::shared_ptr<Base> BasePtr;

class DerivedA : public Base
{
    public:
        DerivedA(void) = default;
        DerivedA(double a)
            : a_(a) {}

        virtual double func(void) const
        {
            return std::exp(a_);
        }

    private:
        double a_; 

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Base>(*this);
                ar & a_;
            }
}; 


class DerivedB : public Base
{
    public:
        DerivedB(void) = default;
        DerivedB(double b)
            : b_(b) {}

        virtual double func(void) const
        {
            return std::log(b_);
        }

    private:
        double b_; 

        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & boost::serialization::base_object<Base>(*this);
                ar & b_;
            }
}; 

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Base)
BOOST_CLASS_EXPORT_KEY(DerivedA)
BOOST_CLASS_EXPORT_KEY(DerivedB)

void out(std::string filename)
{
    std::vector<BasePtr> objects;
    BasePtr m1(new DerivedA(1.0));
    BasePtr m2(new DerivedB(4.0));
    objects.push_back(m1);
    objects.push_back(m2);

    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa.template register_type<DerivedA>();
    oa.template register_type<DerivedB>();

    oa << objects;
}

std::vector<BasePtr > in(std::string filename)
{
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);
    ia.template register_type<DerivedA>();
    ia.template register_type<DerivedB>();

    std::vector<BasePtr> objects;

    ia >> objects;

    return objects;
}

int main()
{
    out("test.out");
    auto r = in("test.out");
    return r.size();
}
