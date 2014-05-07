#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/chrono.hpp>

using hr_clock   = boost::chrono::high_resolution_clock;
using time_point = boost::chrono::time_point<hr_clock>;

namespace boost { namespace archive {

    template<class Archive, typename clock>
        void load(Archive& ar, boost::chrono::time_point<clock>& tp, unsigned)
        {
            using namespace boost::chrono;
            
            milliseconds::rep millis;

            ar & millis;
            tp = time_point<clock>(milliseconds(millis));
        }

    template<class Archive, typename clock>
        void save(Archive& ar, boost::chrono::time_point<clock> const& tp, unsigned)
        {
            using namespace boost::chrono;

            milliseconds::rep millis = duration_cast<milliseconds>(tp.time_since_epoch()).count();
            ar & millis;
        }

    template<class Archive, typename clock>
        inline void serialize(Archive & ar, boost::chrono::time_point<clock>& tp, unsigned version)
        {
            boost::serialization::split_free(ar, tp, version);
        }
} }

struct myTimestamp
{
    time_point  begin1;
    time_point  end1;

  private:
    friend class boost::serialization::access;
    template<class Archive>
        void serialize(Archive &ar, unsigned)
        {
            ar & begin1;
            ar & end1;
        }

  public:
    myTimestamp()
        : begin1(hr_clock::now()),
            end1(hr_clock::now() + boost::chrono::hours(1))
    {  }
    virtual  ~myTimestamp() { }
};

#include <sstream>

int main()
{
    std::stringstream ss;
    {
        myTimestamp ts;
        boost::archive::text_oarchive oa(ss);
        oa << ts;
    }

    {
        myTimestamp ts;
        boost::archive::text_iarchive ia(ss);
        ia >> ts;

        sleep(3);
        myTimestamp ref;
        {
            boost::archive::text_oarchive oa(std::cout);
            oa << ts;
        }
        {
            boost::archive::text_oarchive oa(std::cout);
            oa << ref;
        }
    }
}
