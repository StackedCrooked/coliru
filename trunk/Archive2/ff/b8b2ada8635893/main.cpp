#include <string>

class Pet
{
public:
Pet( );
Pet( std::string name, std::string variety, std::string says )
{
    using namespace std;
    name=myName;
    variety=myVariety;
    says=howIspeak;
}

std::string getName( ) const
{
    return myName;
};
std::string getVariety( ) const
{
    return myVariety;
};

virtual void speak( );

protected:
std::string myName;
std::string myVariety;
std::string howIspeak;
};

int main() {

}