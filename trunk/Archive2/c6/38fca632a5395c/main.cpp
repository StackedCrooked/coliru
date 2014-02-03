#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
#include <string>
using std::string;

namespace ProjectIV
{
  class Monster
  {
  friend ostream &operator<< (ostream &out, const Monster &monster);
  public:
    Monster(int con);
  private:
    int con;
  };
} /* namespace ProjectIV */

ostream& ProjectIV::operator<< (ostream &out, const ProjectIV::Monster &monster)
{
  cout << "Constitution: " << monster.con << endl;

  return out;
}

ProjectIV::Monster::Monster(int con): con(con)
{}

using namespace ProjectIV;

int main()
{
  Monster Gojira(140);
  cout << Gojira << endl;
  return 0;
}