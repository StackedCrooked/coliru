#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

class Robot
{
private: 
    double rychlost;
public:
    Robot()
    {
        this->rychlost= 0;
        cout << "Vse je nastaveno, muzeme vyjet" << endl;
    }
    
    double VratMaximalniRychlost()
    {
        return 10;    
    }
    
    void NastavRychlost(double rychlost)
    {
        if(rychlost >= VratMaximalniRychlost())
        {
            cout << "Tato rychlost me rozbije na kusy!!! " << rychlost << "km/h" << endl;
            throw std::length_error("Prekrocena maximalni rychlost!");
        }
        this->rychlost= rychlost;
        cout << "Jedu rychlosti: " << this->rychlost << endl;
    }
    void Zastav()
    {
        this->rychlost= 0;
        cout << "Bezpecne jsem zastavil" << endl;
    }
    
    ~Robot()
    {
        cout << "Obsluha robota byla ukoncena" << endl;
        if(this->rychlost > 0)
        {
            cout << "Robot porad jede, pokusim se ho zastavit" << endl;
            Zastav();
        }
    }
};

int main()
{
    //shared_ptr<Robot> robot2 = make_sharred<Robot>();
    Robot Robot;
    try
    {
        Robot.NastavRychlost(7);
        Robot.NastavRychlost(18);
    }
    catch (std::length_error& error)
    {
        cout << error.what() << endl;
    }
    Robot.NastavRychlost(5);
    return 0;
}