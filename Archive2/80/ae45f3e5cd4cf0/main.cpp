#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/valarray.hpp>
#include <chrono>
#include <memory>

namespace EDIN
{
    struct Region
    {
        int id;
        Region(int id = 42) : id(id) {}

      private:
        friend class boost::serialization::access;
        template<class Archive> void serialize(Archive & ar, const unsigned int file_version)
        {
            ar & id;
        }
    };

    struct Scheme
    {
        std::string GetSchemeType() const { return "scheme_type_42"; }
    };


    class World
    {
        // dummy members to make it compile
        // will be different things of course
        int mass, epoch;
        std::chrono::system_clock::time_point _start;

        std::string report;
      public:
        std::vector<int> cellSequence; // for demo, public

        World(std::string&, EDIN::Region&, unsigned int&, const std::chrono::system_clock::time_point&)
            : mass(99), epoch(88), _start(std::chrono::system_clock::now()), report("Report101")
        {
            // TODO!
        }

        Region       Bounds() const { return Region();       }
        int          Epoch()  const { return epoch;          }
        EDIN::Scheme Scheme() const { return EDIN::Scheme(); }
        std::chrono::system_clock::time_point StartingWallTime() const {
            return _start;
        }

        World()
            : mass(99), epoch(88), _start(std::chrono::system_clock::now()), report("Report101")
        {
        }

        friend void SaveWorld(World* world, char const filename[]);
        friend World* LoadWorld(char const filename[]);

        private:
            friend class boost::serialization::access;
            template<class Archive> void serialize(Archive & ar, const unsigned int file_version)
            {
                ar & mass & epoch;
            }
    };
}

namespace boost
{
    namespace serialization
    {
        template<class Archive>
        inline void save_construct_data(Archive & ar, EDIN::World const * t, unsigned const int file_version)
        {
            time_t const totalRunningTime = std::chrono::duration_cast<std::chrono::duration<time_t, std::milli>>(
                std::chrono::system_clock::now() - t->StartingWallTime()).count();

            EDIN::Region const bounds = t->Bounds();
            time_t const epoch = t->Epoch();

            std::string tmp = t->Scheme().GetSchemeType();
            ar
                << bounds
                << epoch
                << totalRunningTime 
                << tmp;
        }

        template<class Archive>
        inline void load_construct_data(Archive & ar, EDIN::World * t, const unsigned int file_version)
        {
            EDIN::Region bounds;
            unsigned epoch;
            time_t totalRunningTime;
            std::string schemeType;
            ar >>
                bounds >>
                epoch >>
                totalRunningTime >>
                schemeType;

            std::chrono::system_clock::time_point const startingWallTime =
                std::chrono::system_clock::now() - std::chrono::duration<time_t, std::milli>(totalRunningTime);

            ::new(t) EDIN::World(schemeType,bounds,epoch,startingWallTime);
        }
    }
}

#include <fstream>

namespace EDIN {
    void SaveWorld(World* world, char const filename[])
    {
        std::ofstream ofs(filename);

        boost::archive::text_oarchive oa(ofs);

        oa << world << world->cellSequence << world->report;
    }

    World* LoadWorld(char const filename[])
    {
        World *world = 0;

        std::ifstream ifs("world.save");
        boost::archive::text_iarchive ia(ifs);

        ia >> world;
        ia >> world->cellSequence >> world->report;

        return world;
    }
}

int main()
{
    using namespace EDIN;
    std::unique_ptr<World> world(new World);

    world->cellSequence.push_back(12345);
    world->cellSequence.push_back(-6767);
    SaveWorld(world.get(), "world.save");

    world.reset(LoadWorld("world.save"));
    SaveWorld(world.get(), "world2.save");
}
