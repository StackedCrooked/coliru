#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    auto const data = R"(2
Mathematics
&
Ashley
7961000
Doto
99
C++
99
Meh
100
&
Dwayne
7961222
Quantum
99
heh
99
Computing
99 )";

    istringstream filein(data);
    
    int studentSize; 
    string programme, course1, course2, course3;
    filein >> studentSize;
    filein >> programme;
    filein.ignore();
    
    std::string name;
    int id;
    int mark1, mark2, mark3;
    std::string repeat_tag;
    
    while(
      filein >> repeat_tag && repeat_tag == "&" &&
      getline(filein >> ws, name) &&
      filein >> id &&
      getline(filein >> ws, course1) &&
      filein >> mark1 &&
      getline(filein >> ws, course2) &&
      filein >> mark2 &&
      getline(filein >> ws, course3) &&
      filein >> mark3)
    {
        std::cout << "loop\n";
        if( programme == "Physics" )
        {
            /*for(int i=0; i < studentSize; i++)
            {
                phys.push_back(new physics());
                phys[i]->setNameId(name, id);
                phys[i]->addCourse(course1, mark);
                phys[i]->addCourse(course2, mark);
                phys[i]->addCourse(course3, mark);
                sRecord[id] = phys[i];
            }*/
        }
    }
}