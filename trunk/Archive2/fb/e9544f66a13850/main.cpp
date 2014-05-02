#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <sstream>

struct A
{
    std::string oldname;
    std::string newname;

    A(std::string oldname = "", std::string newname = "") 
        : oldname(std::move(oldname)), newname(std::move(newname)) 
    { }

    bool operator==(A const& other) const {
        return (oldname == other.oldname)
            && (newname == other.newname);
    }

    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive &ar, unsigned) {
            ar & oldname;
            ar & newname;
        }
};

struct Example
{
    typedef std::map<std::string, boost::shared_ptr<A> > MapOfA;

    bool check;
    MapOfA mapOfA;

    bool operator==(Example const& other) const {
        return (check == other.check)
            && (mapOfA.size() == other.mapOfA.size())
            && (mapOfA.end() == std::mismatch(
                    mapOfA.begin(),       mapOfA.end(),
                    other.mapOfA.begin(),
                    &ComparePair
            ).first);
    }

  private:
    typedef MapOfA::value_type Pair;
    static bool ComparePair(Pair const& a, Pair const& b) {
        return (a.first == b.first)
            && (!(a.second || b.second) || (*a.second == *b.second));
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, unsigned) {
        ar & check;
        ar & mapOfA;
    }
};

template <typename T>
std::string to_string(T const& o) {
    std::stringstream ss; 
    boost::archive::text_oarchive oa(ss);
    oa << o;
    return ss.str();
}

int main()
{
    Example const data = {
        false,
        { { "ONE", boost::make_shared<A>("old one","new one") },
          { "TWO", boost::make_shared<A>("old two","new two") },
          { "TRHEE", boost::make_shared<A>("old three","new three") },
        }
    };

    std::string const original = to_string(data);

    std::cout << original << "\n";

    {
        std::stringstream ss(original); 
        boost::archive::text_iarchive ia(ss);

        Example roundtrip;
        ia >> roundtrip;

        std::string const verification = to_string(roundtrip);

        std::cout << std::boolalpha;
        std::cout << "Matching: "   << (data == roundtrip)        << "\n";
        std::cout << "Serialized: " << (verification == original) << "\n";
    }
}
