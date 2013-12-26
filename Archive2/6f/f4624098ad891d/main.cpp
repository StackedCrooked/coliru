// ========== HEADER ==========

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employees {
    virtual void printStats(std::ostream& out) const=0;
    
    string mFirstName;
    string mLastName;
    int mSalary;
};

std::ostream& operator<<(std::ostream& out, const Employees& employee) ;
std::ostream& operator<<(std::ostream& out, const vector<Employees*>& midzer)

struct Manager: public Employees {
    Manager(const char* f, const char* l, int s, int m, int v);    
    virtual void printStats(std::ostream& out) const;
    int mNumberOfMeetingsPerWeek;
    int mNumberOfVacationDaysPerYear;    
};

// ========== CPP ==========

Manager::Manger(const char* f, const char* l, int s, int m, int v)
:mFirstName(f), mLastName(l), mSalary(s), mNumberOfMeetingsPerWeek(m), mNumberOfVacationDaysPerYear(v)
{}

void Manager::printStats(std::ostream& out) const //function doesn't modify, so const
{
    out << "\nManager." << endl;
    out << "First name: " << mFirstName << endl; // data member of base class
    out << "Last name: " << mLastName << endl; // data member of base class
    out << "Salary: " << mSalary << endl; // data member of base class
    out << "Meetings per week: " << mNumberOfMeetingsPerWeek << endl; // data member of derived class
    out << "Vacation Days per year: " << mNumberOfVacationDaysPerYear << endl; //data member of derived class
    out << endl;
}
std::ostream& operator<<(std::ostream& out, const Employees& employee) 
{
   employee.printStats(out);
   return out; //return ostreams by reference when done
}
std::ostream& operator<<(std::ostream& out, const vector<Employees*>& midzer) 
{
   for (vector<Employees*>::const_iterator i = midzer.begin(); i != midzer.end(); ++i)
   {
       out << *(*i);
   }
   //or if you have a newer compiler:
   //for (Employees* i : midzer) out << *i;
   return out; //return ostreams by reference when done
}

int main() {
    vector<Employees*> midzer;
    midzer.push_back(new Manager("Bob", "Smith", 23456, 41, 3));
    ofstream outfile;
    outfile.open("/users/mundt/desktop/EmployeeDatabase.txt");
    outfile << midzer; //well that's easy
    outfile.close();
    cout << midzer;
}