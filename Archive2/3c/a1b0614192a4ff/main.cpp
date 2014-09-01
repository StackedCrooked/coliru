#include <iostream>
#include <fstream>
using namespace std;

class student
{
    public:
    char s;
    int age;
};

ostream& operator<<(ostream &output, const student &s) 
{
      output << s.s << " " << s.age;
      return output;

}

int main (void)
{
    student a;
    a.s = 'a';
    a.age = 1;
    ofstream myfile;
    myfile.open("a1.txt",ios::app);
    myfile << &a;
    return 0;
}