#include <boost/serialization/optional.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/list.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/make_shared.hpp>

struct SomeStruct {
    int x;
    double y;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &at, const unsigned int version) {
        at & x;
        at & y;
    }

};

class BuildTest {
  public:

    std::list<boost::shared_ptr<SomeStruct>> lss ;
    std::string name;

  private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &at, const unsigned int version) {
        at & lss;  // is this sufficient to serialize lss ?
        at & name;
    }

};

int main() {
    BuildTest bt;
    bt.name = "Let's try this";
    bt.lss = { boost::make_shared<SomeStruct>(), boost::make_shared<SomeStruct>() };
    boost::archive::text_oarchive oa(std::cout);
    oa << bt;
}
