
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Employee
{
    string firstName;
    string lastName;
};

struct Company
{
    int id;
    string title;
    string summary;
    int numberOfEmployees() { return employees.size(); }
    vector<Employee> employees;
};

vector<Company> companies;

int main()
{
    Company c { 1, "MyBiz", "We Code Stuff", {} };
    c.employees.push_back( Employee{"Anna","Smith"} );
    c.employees.push_back( Employee{"Donald","Brown"} );
    
    companies.push_back(c);

}
