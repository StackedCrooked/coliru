#include <iostream>
using namespace std;


#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#include <string>
#include <vector>
class Perso{ public :
    Perso(std::string name = "IA", float points = 100);
    std::string ChangeNameRnd(std::vector<std::string> A);
    std::string ChangeName(std::string A);
    int Degats(float deg);
    int Battle();
    int Fighting(Perso& a, float points = 10);
    void Show() const;
protected:
    float c_points{};
    int c_battle{};
    std::string c_name{};
};
 
class Ultim : public Perso{ public:
    using Perso::Perso;
    int Fighting(Perso& a, float points = 10);
private:
    float u_points{};
    std::string u_name{};
};

Perso::Perso(std::string name, float points) : c_name(name), c_points(points) {}
 
string Perso::ChangeNameRnd(vector<string> A){srand(time(0));
    int const B = rand() % A.size();
    return c_name = A.at(B);
}
 
string Perso::ChangeName(string A){
    return c_name = A;
}
 
int Perso::Degats(float deg){
    if(c_points > 100)
        c_points = 100;
    else if (c_points < 0)
        c_points = 0;
 
        c_points -= deg;
    return c_points;
}
 
int Perso::Battle(){
    return ++c_battle;
}
 
int Perso::Fighting(Perso& a, float points){
    a.Battle();
    return a.Degats(points);
}
 
int Ultim::Fighting(Perso& a, float points){
    return a.Degats(points);
}
 
void Perso::Show() const{
    cout << "Name: " << c_name << endl;
    cout << "Points: " << c_points << endl;
    if(c_battle <= 0)
        cout << "Je me suis pas fais defoncer " << endl;
    else
        cout << "Je me suis fais defoncer " << c_battle << " fois" << endl;
}

int main()
{
    Perso A{}; Ultim B{"Ultim", 100};
    B.Fighting(A);
    A.Show();
}