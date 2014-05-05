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

        struct World : boost::noncopyable
        {
            List list;
            GameObject* the_object;

            World() : the_object(nullptr) {}
            ~World() { delete the_object; }

        private:
            friend boost::serialization::access;
            template<class Archive>
                void serialize(Archive & ar, unsigned) {
                    ar & list;
                    ar & the_object;
                }
        };

std::string serialize(World const& w)
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);

    oa << w;

    return ss.str();
}

void deserialize(std::string const& input, World& w)
{
    std::stringstream ss(input);
    boost::archive::text_iarchive ia(ss);

    ia >> w;
}

int main()
{
    World world;
    for (int i = 0; i < 10; ++i)
        world.list.areas.push_back(new Area(i));

    // build original obj
    world.the_object = new GameObject(world.list.areas[3]); // sharing the area pointer from the list

    std::string const serialized = serialize(world);
    std::cout << serialized << '\n';
    std::cout << "-------------------------------------------------\n";

    // create roundtrip
    World roundtrip;
    deserialize(serialized, roundtrip);
    std::cout << "EQUAL? " << std::boolalpha << (serialized == serialize(roundtrip)) << "\n";
}
