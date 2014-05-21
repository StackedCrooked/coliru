#include <iostream>
#include <string>
#include <fstream>
#include "boost/program_options.hpp"

using std::cout;
using std::string;
using std::endl;
using std::ifstream;

namespace gOp = boost::program_options;

struct prgVars
{
    string name;
    int id;
    string gDiff;

    float encRand;
    float pDMod;
    float cDMod;
    int iRLow;
    int iRHigh;
};

void loadGData(prgVars& pgv);

int main()
{
    prgVars pgv;

    cout << "Testing ini reading...." << endl;

    system("Pause");

    loadGData(pgv);

    cout << "Loaded values:            " << endl;
    cout << "Name:                     " << pgv.name    << endl;
    cout << "ID:                       " << pgv.id      << endl;
    cout << "gDiff:                    " << pgv.gDiff   << endl 
                                                        << endl;

    cout << "Game Difficulty Values:   " << endl;
    cout << "Encounter Randomness:     " << pgv.encRand << endl;
    cout << "Player Damage Modifier:   " << pgv.pDMod   << endl;
    cout << "Computer Damage Modifier: " << pgv.cDMod   << endl;
    cout << "Item Range Low:           " << pgv.iRLow   << endl;
    cout << "Item Range High:          " << pgv.iRHigh  << endl;

    system("Pause");
}

void loadGData(prgVars& pgv)
{
    gOp::options_description desc("Settings");
    desc.add_options()
        ("PLAYERDATA.NAME" , gOp::value<string>(&pgv.name) , "player_name")
        ("PLAYERDATA.ID"   , gOp::value<int>(&pgv.id)      , "player_id")
        ("PLAYERDATA.GDIFF", gOp::value<string>(&pgv.gDiff), "game_difficulty");

    gOp::variables_map vm;

    try
    {
        ifstream settings_file("input.txt",ifstream::in);
        gOp::store(gOp::parse_config_file(settings_file, desc), vm);
        settings_file.close();
        gOp::notify(vm);
    }

    catch (const gOp::error& e )
    {
        std::cerr << e.what() << std::endl;
    }

    if (pgv.gDiff == "Easy")
    {

        gOp::options_description desc("DVars");
        desc.add_options()
            ("EASY.ERAND", gOp::value<float>(&pgv.encRand), "encounter_rate")
            ("EASY.PDMOD", gOp::value<float>(&pgv.pDMod),   "player_damage_bonus")
            ("EASY.CDMOD", gOp::value<float>(&pgv.cDMod),   "computer_damage_bonus")
            ("EASY.IRL",   gOp::value<int>(&pgv.iRLow),     "item_rng_low")
            ("EASY.IRH",   gOp::value<int>(&pgv.iRHigh),    "item_rng_high");

        gOp::variables_map vm;

        ifstream settings_file("input.txt",ifstream::in);
        gOp::store(gOp::parse_config_file(settings_file, desc), vm);
        settings_file.close();
        gOp::notify(vm);
    }

    else if (pgv.gDiff == "Medium")
    {
        gOp::options_description desc("DVars");
        desc.add_options()
            ("MEDIUM.ERAND", gOp::value<float>(&pgv.encRand), "encounter_rate")
            ("MEDIUM.PDMOD", gOp::value<float>(&pgv.pDMod),   "player_damage_bonus")
            ("MEDIUM.CDMOD", gOp::value<float>(&pgv.cDMod),   "computer_damage_bonus")
            ("MEDIUM.IRL",   gOp::value<int>(&pgv.iRLow),     "item_rng_low")
            ("MEDIUM.IRH",   gOp::value<int>(&pgv.iRHigh),    "item_rng_high");

        gOp::variables_map vm;

        ifstream settings_file("input.txt",ifstream::in);
        gOp::store(gOp::parse_config_file(settings_file, desc), vm);
        settings_file.close();
        gOp::notify(vm);
    }

    else if (pgv.gDiff == "Hard")
    {
        gOp::options_description desc("DVars");
        desc.add_options()
            ("HARD.ERAND", gOp::value<float>(&pgv.encRand), "encounter_rate")
            ("HARD.PDMOD", gOp::value<float>(&pgv.pDMod),   "player_damage_bonus")
            ("HARD.CDMOD", gOp::value<float>(&pgv.cDMod),   "computer_damage_bonus")
            ("HARD.IRL",   gOp::value<int>(&pgv.iRLow),     "item_rng_low")
            ("HARD.IRH",   gOp::value<int>(&pgv.iRHigh),    "item_rng_high");

        gOp::variables_map vm;

        ifstream settings_file("input.txt",ifstream::in);
        gOp::store(gOp::parse_config_file(settings_file, desc), vm);
        settings_file.close();
        gOp::notify(vm);
    }
}
