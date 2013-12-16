#include <string>
using std::string;

class Armor {

private:
    int m_weight;

public:
    Armor(int weight);

};

//#include "Armor.h"
class Knight {
private:
    Armor* m_armor;
    string m_name;
    int m_strength;

public:
    Knight(string name, int strength);

    void setArmor(Armor* armor);
}

//#include "Knight.h"
void Knight::setArmor(Armor* armor){
    m_armor = armor; // error occurred

}