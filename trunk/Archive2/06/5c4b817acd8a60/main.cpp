#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/version.hpp>
#include <sstream>

struct DataV0
{
    float f = 3.14;
    int   i = 42;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        if (0 != version) 
        {
            throw std::runtime_error("Unsupported version");
        }
        ar & f;
        ar & i;
    }
};

struct DataV1
{
    double d  = 3.14;
    size_t ul = 42;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        switch(version)
        {
            case 0:
                { 
                    DataV0 old;
                    ar & old.f;
                    ar & old.i;

                    d = old.f;
                    assert(old.i >= std::numeric_limits<size_t>::min());
                    assert(old.i <= std::numeric_limits<size_t>::max());
                    ul = static_cast<size_t>(old.i);
                }
                break;
            case 1:
                ar & d;
                ar & ul;
                break;
        }
    }
};

BOOST_CLASS_VERSION(DataV1, 1)

template <typename Data>
std::string to_string(Data d)
{
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);

    oa << d;

    return oss.str();
}

template <typename Data>
bool verify(std::string const& text)
{
    std::istringstream iss(text);
    boost::archive::text_iarchive ia(iss);

    Data d;
    ia >> d;

    return text == to_string(d);
}

int main()
{
    std::string v0text = to_string(DataV0());
    std::string v1text = to_string(DataV1());

    std::cout << v0text << '\n';
    std::cout << v1text << '\n';

    std::cout << "v0 as v0: " << std::boolalpha << verify<DataV0>(v0text) << "\n";
    std::cout << "v0 as v1: " << std::boolalpha << verify<DataV1>(v0text) << "\n";

    std::cout << "v1 as v1: " << std::boolalpha << verify<DataV1>(v1text) << "\n";
    try {
        std::cout << "v1 as v0: " << std::boolalpha << verify<DataV0>(v1text) << "\n";
    } catch (std::exception const& e)
    {
        std::cerr << "Threw the expected '" << e.what() << "'\n";
    }

}

