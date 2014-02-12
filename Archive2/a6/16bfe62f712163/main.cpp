#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


int GetRandom(int x){return rand()%x;}

class Bunny
{

private:
    static const vector <string> F_names;
    static const vector <string> M_names;
    static const vector <string> colors;
    bool isMale= GetRandom(2)<1 ? true : false;
    bool isVampire= GetRandom(100)< 2 ? true : false;
    string name;
    string color;
    string sex;
    string vampire;
    int age;
    void Inner(){
        age=0;
        sex= isMale ? "male" : "female";
        name= isMale ? M_names[GetRandom(10)] : F_names[GetRandom(5)];
        if(isVampire) cout<< "Radioactive mutant vampire ";
        cout<< "Bunny "<< name<< " was born."<<endl;
        vampire= isVampire? "yes":"no";
        }

public:

    Bunny()                                                     //DEFAULT CONSTRUCTOR
    { color=colors[GetRandom(4)]; Inner();}
    Bunny(string C)                                             //CHILDREN CONSTRUCTOR
    { color=C; Inner();}
    ~Bunny()                                                    //DESTRUCTOR
    {
        if(isVampire)cout<<"Radioactive mutant vampire ";
        cout<<"Bunny "<< name <<" died!"<<endl;
    }
    friend bool operator>  (  const Bunny&,  const Bunny&)  ; // **** made const correct
    bool isMature() const {if(  (age>=2) &&(isMale) )return true; return false;}
    bool getIsMale() const {return isMale;}
    string getName() const {return name;}
    string getColor() const {return color;}
    string getSex()const {return sex;}
    string getVampire() const{return vampire;}
    bool getIsVampire() const {return isVampire;}
    int getAge() const {return age;}

    void RemoveABunny();
    void PrintInfo();
    void increaseAge();
};

    const vector <string> Bunny::F_names={"Hajra","Mejra","Sefika","Hanifa","Zulfa"};
    const vector <string> Bunny::M_names={"Wayne Rooney","Cristiano Ronaldo","Edin Dzeko",
    "Robin Van Persie","Juan Mata","David De Gea","Luis Nani","Ryan Giggs","Paul Scholes","David Beckham"};
    const vector <string> Bunny::colors={"white","brown","black","spotted"};

     bool operator> ( const Bunny& a,  const Bunny& b) {return (a.age)>(b.age);}


    /*const*/ void AddBabyToColony(const string &Clr, vector<Bunny> & Colony) // removed const on return type  
    {
        Colony.emplace_back(Clr); // **** use emplace_back instead of push_back
                                  // avoid the creation and destruction of a temporary bunny object     
    }

    void PrintColony(const vector<Bunny> & Colony ,int x=0 ) // removed const on return type
    {
        cout<<"\n\nColony information in turn number: "<< x<<endl;
        cout<<"AGE\t\tSEX\t\tCOLOR\t\tVAMPIRE STATUS\t\tNAME\n";
        for( std::size_t i=0; i<Colony.size() ; i++)
        {
            cout<<Colony[i].getAge()<<"\t\t"<<Colony[i].getSex()<<"\t\t"<<Colony[i].getColor();
            cout<<"\t\t"<<Colony[i].getVampire()<<"\t\t"<<Colony[i].getName()<<"\n"<<endl;
        }
        cout<<"\n\n\n";
    }

int main()
{
    int Males=0;
    //int Females=0;
    int Total=5;
    srand(time(0));
    
    //vector <Bunny> BunnyColony(Total);
    
    vector <Bunny> BunnyColony ; // create an empy vector
    BunnyColony.reserve(1000) ; // reserve space dor 1000 bunnies
    BunnyColony.resize(Total) ; // put in the initial 'Total' bunnies
    
    for( int i=0 ; i< 5; i++) if(BunnyColony[i].getIsMale()) Males++;

    PrintColony(BunnyColony);                    //HERE EVERYTHING IS OK

    AddBabyToColony("Red",BunnyColony);    //BUT THE THE PROBLEM IS HERE

    

    cout<<"Done\n";
    return 0;
}
