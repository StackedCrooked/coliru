#include <boost/archive/text_oarchive.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>
#include <boost/date_time/local_time/local_time.hpp>

struct parameter_strings {};

struct MyData
{
    std::string id;
    std::string name;
    boost::posix_time::ptime time; 

  private:
    friend class boost::serialization::access;
    template <typename Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar & id;
            ar & name;
            ar & time;  // when i comment this line, error goes off
        } 

  public:
    MyData() : time(boost::posix_time::not_a_date_time) { }
    MyData(parameter_strings const&) : time(boost::posix_time::not_a_date_time) { }
    virtual ~MyData() { };
};

int main()
{
    boost::archive::text_oarchive oa(std::cout);
    MyData data;

    oa << data;
}
