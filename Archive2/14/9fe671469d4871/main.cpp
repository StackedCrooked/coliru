#include <string>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/config.hpp>

template <class T> class classOne {
public:
    classOne(){};
    classOne(T val) : st(val){};
    virtual ~classOne() {};
    virtual double GetError() = 0;
protected:  T st;
private:
    friend class boost::serialization::access;
protected:
    template<class archive>
    void serialize(archive& ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(st);
    }
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(classOne<double>);

template <class T> class classTwo : public classOne<T>
{
public:
    classTwo() : classOne<T>(1.0), error(0){};
    classTwo(T val) : classOne<T>(val), error(val){};
    virtual T GetError() { return error; };

private:
    T error;
    friend class boost::serialization::access;
    template<class archive>
    void serialize(archive& ar, const unsigned int version)
    {
#if 0
        classOne<T>::serialize(ar, version);
#else
        ar & boost::serialization::make_nvp("base", static_cast<classOne<T>&>(*this));
#endif
        ar & BOOST_SERIALIZATION_NVP(error);
    }
};

#include <fstream>

int main(int argc, char** argv)
{
    classTwo<double> ch2(0.5);
    std::ofstream ofs2("test2.xml");
    boost::archive::xml_oarchive oa2(ofs2);
    oa2 << BOOST_SERIALIZATION_NVP(ch2);
    ofs2.close();
}
