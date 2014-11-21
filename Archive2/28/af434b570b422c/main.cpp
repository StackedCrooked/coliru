#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


using namespace boost::property_tree;

struct X {
    void add_junction(std::string repID, ptree& pt) const {
        std::string juncs  = _roadID;
        std::size_t pos    = juncs.find_last_of("j");
        std::string jstart = juncs.substr(0,pos);
        std::string jend   = juncs.substr(pos,juncs.length());

        pt.add(repID + ".startJunction", jstart);
        pt.add(repID + ".endJunction", jend);
    }

    std::string _roadID = "123890234,234898j340234,23495905";
};

int main()
{
    ptree pt;

    X program_data;
    program_data.add_junction("AbbeyRoad", pt);
    program_data.add_junction("Big Ben", pt);
    program_data.add_junction("Trafalgar Square", pt);

    write_ini("report.ini", pt);
}
