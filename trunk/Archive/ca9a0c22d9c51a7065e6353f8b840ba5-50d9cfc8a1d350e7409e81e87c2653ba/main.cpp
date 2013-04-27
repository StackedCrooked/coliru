using namespace std;
#include<string>

using namespace std;

class Employee
{
    protected:
    int employeeNumber;
    string firstName;
    string lastName;
    string address;
    string telephone;
    double salary;
    int generateEmployeeNumber();

    public:
    Employee();
    Employee(string fin, string lan, string add, string tel, double sal);
    void setEmployeeName(string fin, string lan);   //start of setters
    void setEmployeeAddress(string add);
    void setEmployeeTelephone(string tel);
    void setEmployeeSalary(double sal);
    string getEmployeeFirstName();          //start of getters
    string getEmployeeLastName();   
    string getEmployeeAddress();
    string getEmployeeTelephone();
    double getEmployeeSalary();
    int show();
};
//#include"Employee.h"
#include<iostream>
#include<string>

using namespace std;

//start of constructors
Employee::Employee()
{

}

Employee::Employee(string fin, string lan, string add, string tel, double sal)
{
    firstName = fin;
    lastName = lan;
    address = add;
    telephone = tel;
    salary = sal;
}
//end of constructors

//start of setters
void Employee::setEmployeeName(string fin, string lan)
{
    cout<<"Please enter the Employee's first name: ";
    cin>>fin;
    cout<<"Please enter the Employee's last name: ";
    cin>>lan;

    firstName = fin;
    lastName = lan;
}

void Employee::setEmployeeAddress(string add)
{
    cout<<"Please enter the Employee's address: ";
    cin>>add;
    address = add;
}

void Employee::setEmployeeTelephone(string tel)
{
    cout<<"Please enter the Employee's telephone number: ";
    cin>>tel;
    telephone = tel;
}

void Employee::setEmployeeSalary(double sal)
{
    cout<<"Please enter the Employee's monthly salary: R";
    cin>>sal;
    salary = sal;
}
//end of setters

//start of getters
string Employee::getEmployeeFirstName()
{
    return firstName;
}

int main(){
    std::cout<<"Test";
    return 0;
}