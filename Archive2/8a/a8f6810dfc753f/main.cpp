#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
class Applicant
{
public:
 
        Applicant();
        ~Applicant();
        Applicant(string);
        string getUserName();
        void setUserName(string);      
        void createApplicant();
        void viewApplicant(Applicant& form);
        vector<Applicant> thing;
 
private:
        string newUserName;
};
 
Applicant::Applicant()
{
}
 
Applicant::~Applicant()
{
}
 
Applicant::Applicant(string userName)
{
        this -> newUserName = userName;
}
 
string Applicant::getUserName()
{
        return newUserName;
}
 
void Applicant::setUserName(string userName)
{
        newUserName = userName;
}
 
 
void Applicant::createApplicant()
{
        Applicant form;
        string status = "Awaiting Approval";
        form.setUserName("test");
 
        thing.push_back(form);
        //clears data when returning to main menu?
 
        for (int i = thing.size()-1; i >= 0; i--)
        {
              std::cout << "Create Applicant Username: " << thing[i].getUserName() << endl;
                          std::cout << endl;
        }
        viewApplicant(form);
}
 
 
Applicant form;
void Applicant::viewApplicant(Applicant& form)
{
     
        for (size_t i = 0; i < form.thing.size(); i++)  //possibly empty
        {
                        cout << "View Applicant UserName: " << form.thing[i].getUserName() << endl;
        }
}
 
int main()
{
        Applicant cA;
        cA.createApplicant();
}