#include <string>
#include <set>
#include <map>
#include <iostream>

using namespace std;

class Base
{ protected:
    string STR__Description;  // Pardon my non-standard style
  public:
    virtual
    string GetDescription() const
    { return STR__Description;
    }
    void   SetDescription( string str__Description )
    { STR__Description = str__Description;
    }
};

class ArmyBase: public Base
{ public:
    string GetDescription() const
    { return STR__Description + " (Army)";
    }
};

class NavyBase: public Base
{ public:
    string GetDescription() const
    { return STR__Description + " (Navy)";
    }
};

class Cmp
{
public:
    bool operator()(Base const* lhs, Base const* rhs) const
    { return lhs->GetDescription() < rhs->GetDescription(); };
};

int main()
{

    Base                         base;
    ArmyBase                     base_Army;
    set<ArmyBase*, Cmp>           set__ArmyBases;
    map<string, Base*>      map__Bases;
    map<string, Base*>::iterator         iter_Bases;
    NavyBase                     base_Navy;
    set<NavyBase*, Cmp>          set__NavyBases;
    
    
    base_Army = ArmyBase(); 
    base_Navy = NavyBase();
    
    set__ArmyBases.insert(                   &base_Army   );
    map__Bases.insert(     pair<string, Base*>( "Boca Raton",    &base_Army ) );
    
    
    set__NavyBases.insert(                   &base_Navy   );
    map__Bases.insert(     pair<string, Base*>( "NAS Pensacola", &base_Navy ) );
    
    for (auto b: map__Bases)
        std::cout << b.first << "..." << b.second->GetDescription() << std::endl;
}