#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

struct Area
{
    Area(int i):id(i) {}
    int id;
  private:
    Area() { } // used only in deserialization
    friend boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, unsigned) { ar & id; }
};

struct List : boost::noncopyable
{
    std::vector<Area*> areas;

    ~List() {
        std::for_each(areas.begin(), areas.end(), std::default_delete<Area>());
    }
    
  private:
    friend boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, unsigned) { ar & areas; }
};

struct M_Character {
    virtual ~M_Character() {} 
  private:
    friend boost::serialization::access;
    template<class Archive>
        void serialize(Archive & /*ar*/, unsigned) { }
};

struct GameObject : M_Character, boost::noncopyable
{
    Area* area;

    GameObject(Area* area = nullptr) : area(area) {}
    
  private:
    friend boost::serialization::access;
    template<class Archive>
        void serialize(Archive & ar, unsigned) {
            ar & boost::serialization::base_object<M_Character>(*this);
            ar & area;
        }
};

BOOST_CLASS_EXPORT_GUID(GameObject, "GameObject")
#include <sstream>

std::string serialize(M_Character* obj)
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);

    oa << obj;

    return ss.str();
}

M_Character* deserialize(std::string const& input)
{
    std::stringstream ss(input);
    boost::archive::text_iarchive ia(ss);

    M_Character* obj = nullptr;
    ia >> obj;

    return obj;
}

int main()
{
    List l;
    for (int i = 0; i < 10; ++i)
        l.areas.push_back(new Area(i));

    std::unique_ptr<M_Character> obj, roundtrip;
    
    // build original obj
    obj.reset(new GameObject(l.areas[3])); // sharing the area pointer from the list

    std::string const serialized = serialize(obj.get());
    std::cout << serialized << '\n';
    std::cout << "-------------------------------------------------\n";

    // create roundtrip
    roundtrip.reset(deserialize(serialized));
    std::cout << "EQUAL? " << std::boolalpha << (serialized == serialize(roundtrip.get())) << "\n";
}
