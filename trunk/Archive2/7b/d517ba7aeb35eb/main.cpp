#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <fstream>
#include <iostream>

class Simulation {

  public:
    // Constructors
    Simulation(int anzType, int x = 25, int y = 25, int z = 25, int NT = 100, int NS = 500, int NR = 1000, std::string n = "");
    Simulation(); // Defaultconstructor für Boost Serialisierung

    // Destructor
    virtual ~Simulation();

  private:
    std::string name;
    int         NType, NTherm, NStep, NRun;
    int         Lx, Ly, Lz, LyLz;

    friend class boost::serialization::access;

    template <typename Archive> void serialize(Archive &ar, unsigned) {
        ar & name;
        ar & NType;
        ar & NTherm;
        ar & NRun;
        ar & NStep;
    }
};

Simulation::Simulation() {}

Simulation::Simulation(int anzType, int x, int y, int z, int NT, int NS, int NR, std::string n)
  : name(n), NType(anzType), NTherm(NT), NStep(NS), NRun(NR),
    Lx(x), Ly(y), Lz(z), LyLz(y * z)
{
}

Simulation::~Simulation() {}

int main() {
    Simulation *sim = new Simulation(2, 25, 25, 25, 100, 500, 1000, "Sim");
    {
        std::ofstream ofs("output.txt", std::ios::binary);
        boost::archive::text_oarchive oa(ofs);
        oa << sim;
    }

    {
        Simulation* newSim = nullptr;
        std::ifstream ifs("output.txt", std::ios::binary);
        boost::archive::text_iarchive ia(ifs);
        ia >> newSim;

        delete newSim;
    }
}
