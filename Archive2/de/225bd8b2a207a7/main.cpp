#include <string>
#include <map>
#include <iostream>

struct Armor 
{ 
    std::string name ; 
    int b, c, d ; 
    Armor( const char* s, int i, int j, int k ) : name(s), b(i), c(j), d(k) {} 
};

class ArcherArmor
{
    public: std::map <int, Armor> soldier_armor;
    public: void ArcherArmor_shop();
};

void ArcherArmor::ArcherArmor_shop()
{
	soldier_armor = {//name, damage, price
			{1, Armor("Meito Ichimonji", 4, 150, 1)},
			{2, Armor("Shusui", 10, 230, 2)},
			{3, Armor("Apocalypse", 16, 300, 3)},
			{4, Armor("Blade of Scars", 24, 550, 4)},
			{5, Armor("Ragnarok", 32, 610, 5)},
			{6, Armor("Eternal Darkness", 40, 690, 6)},
			{7, Armor("Masamune", 52, 750, 7)},
			{8, Armor("Soul Calibur", 60, 900, 8)}
		};
}
    
int main()
{
    ArcherArmor a ;
    a.ArcherArmor_shop() ;
    
    for( const auto& p : a.soldier_armor ) 
        std::cout << p.first << ' ' << p.second.name << '\n' ;
    
}