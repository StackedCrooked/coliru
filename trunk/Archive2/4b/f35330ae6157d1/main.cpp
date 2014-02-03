#include <iostream>
#include <string>
#include <iomanip> //for displaying table

using namespace std;

class Employee
{
    private:
        string name;
        int idNumber;
        string department;
        string position;

    public:

        //default constructor
        Employee()
        {
            name = "";
            idNumber = 0;
            department = "";
            position = "";
        }

        Employee(string n, int id, string dept, string pos)
        {
            name = n;
            idNumber = id;
            department = dept;
            position = pos;
        }
        Employee(string n, int id)
        {
            name = n;
            idNumber = id;
            department = "";
            position = "";
        }


        void setName(string n)
        {
            name = n;
        }
        void setIdNumber(int id)
        {
            idNumber = id;
        }
        void setDepartment(int dept)
        {
            department = dept;
        }
        void setPosition(string pos)
        {
            position = pos;
        }

        string getName()
        {
            return name;
        }
        int getIdNumber()
        {
            return idNumber;
        }
        string getDepartment()
        {
            return department;
        }
        string getPosition()
        {
            return position;
        }

};

//will make array of employees so they can be easily iterated through and displayed in table
const int NUM_EMPLOYEES = 3;

int main()
{

    Employee employees[NUM_EMPLOYEES];

    employees[0] = {"Susan Meyers", 47899, "Accounting", "Vice President"}; 
    employees[1] = {"Mark Jones", 39119, "IT", "Programmer"};
    employees[2] = {"Joy Rogers", 81774, "Manufacturing", "Engineer"};

    cout << "\n";
    cout << setw(15) << "Employee Name" << setw(15) << "ID Number" << setw(20) << "Department" << setw(20) << "Position";
    cout << "\n\n";


    for (int i = 0; i < NUM_EMPLOYEES; i++)
    {
         cout << setw(15) << employees[i].getName() << setw(15) << employees[i].getIdNumber() << setw(20)
              << employees[i].getDepartment() << setw(20) << employees[i].getPosition() << "\n";
    }

    cout << "\n";
    return 0;
}
