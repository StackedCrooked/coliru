#include <algorithm>
#include <cstdio> // <stdio.h>
#include <cstring> // <string.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int GetRandom(int x){ return x>0 ? rand()%x : 0 ; }

class Bunny
{

private:
    static const vector<string> F_names ;
    static const vector<string> M_names ;
    static const vector<string> colors ;

    string name;
    string color = colors[ GetRandom( colors.size() ) ];
    int age = 0 ;
    bool isMale = GetRandom(2) == 0  ;
    string sex ;
    bool isVampire = GetRandom(10) < 2 ; // 20%
    string VampireString;

    void init()
    {
        sex = isMale ? "Male" : "Female" ;
        name = isMale ? M_names[ GetRandom( M_names.size() ) ] :
                        F_names[ GetRandom( F_names.size() ) ] ;
        VampireString = isVampire ? "Radioactive vampire mutant" : "normal" ;
        if( isVampire ) std::cout << "Radioactive mutant vampire " ;
        std::cout << "Bunny " << name << " (" << color << ") was born!\n" ;
    }

public:

    Bunny() { init() ; }
    Bunny( string clr ) { init() ; color = clr ; }

    ~Bunny()
    {
        if(isVampire) cout<<"Radioactive mutant vampire " ;
        cout << "Bunny " << name << " (" << color << ") died!\n" ;
    }

    bool getIsMale() const {return isMale;}
    string getName() const {return name;}
    string getSex() const {return sex;}
    string getColor() const {return color;}
    int getAge() const {return age;}
    bool isMature() const { return age >= 2 && isMale ; }

    void AddBabyToColony() {}
    void RemoveABunny() {}
    void PrintInfo() {}
};

const vector<string> Bunny::F_names = {"Hajra","Mejra","Sefika","Hanifa","Zulfa"};
const vector<string> Bunny::M_names = {"Wayne Rooney","Cristiano Ronaldo","Edin Dzeko","Robin Van Persie","Juan Mata"};
const vector<string> Bunny::colors = {"white","brown","black","spotted"};

int main()
{
    int Total=5;
    srand(time(0));
    std::vector<Bunny> BunnyColony(Total);

    int Males=0;
    for( const Bunny& b : BunnyColony ) if( b.getIsMale() ) ++Males ;
    // int Females = BunnyColony.size() - Males ;

    std::cout.clear(std::ios::failbit) ; // silence cout
    std::sort( BunnyColony.begin(), BunnyColony.end(),
                []( const Bunny& a, const Bunny&b ) { return a.getAge() < b.getAge() ; } ) ;
    std::cout.clear() ; // unsilence cout

    for( const Bunny& b : BunnyColony )
        cout << "Bunny " << b.getName() << " is " << b.getAge() << " year's old.\n" ;

    cout << "Done\n" ;
}
